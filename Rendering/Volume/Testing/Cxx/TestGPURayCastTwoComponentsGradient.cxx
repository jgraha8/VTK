#include <vtkSmartPointer.h>
#include <vtkPlanes.h>
#include <vtkCamera.h>
#include <vtkSphereSource.h>

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>


/*=========================================================================
Program:   Visualization Toolkit
Module:    TestGPURayCastTwoComponentsIndependent.cxx
Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
All rights reserved.
See Copyright.txt or http://www.kitware.com/Copyright.htm for details.
This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.
=========================================================================*/

// Description
// This test creates a vtkImageData with two components.
// The data is volume rendered considering the two components as independent.

#include "vtkCamera.h"
#include "vtkColorTransferFunction.h"
#include "vtkGPUVolumeRayCastMapper.h"
#include "vtkImageData.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkNew.h"
#include "vtkPiecewiseFunction.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkTesting.h"
#include "vtkTestUtilities.h"
#include "vtkVolume.h"
#include "vtkVolumeProperty.h"
#include "vtkUnsignedShortArray.h"

static const char * TestGPURayCastTwoComponentsIndependentLog =
"# StreamVersion 1\n"
"EnterEvent 298 198 0 0 0 0 0\n"
"MouseMoveEvent 298 198 0 0 0 0 0\n"
"MouseMoveEvent 292 200 0 0 0 0 0\n"
"MouseMoveEvent 285 200 0 0 0 0 0\n"
"MouseMoveEvent 281 202 0 0 0 0 0\n"
"MouseMoveEvent 277 202 0 0 0 0 0\n"
"MouseMoveEvent 274 203 0 0 0 0 0\n"
"MouseMoveEvent 270 205 0 0 0 0 0\n"
"MouseMoveEvent 266 205 0 0 0 0 0\n"
"MouseMoveEvent 262 205 0 0 0 0 0\n"
"MouseMoveEvent 260 205 0 0 0 0 0\n"
"MouseMoveEvent 258 206 0 0 0 0 0\n"
"MouseMoveEvent 255 206 0 0 0 0 0\n"
"MouseMoveEvent 253 207 0 0 0 0 0\n"
"MouseMoveEvent 251 207 0 0 0 0 0\n"
"MouseMoveEvent 250 207 0 0 0 0 0\n"
"MouseMoveEvent 248 207 0 0 0 0 0\n"
"MouseMoveEvent 244 207 0 0 0 0 0\n"
"MouseMoveEvent 237 208 0 0 0 0 0\n"
"MouseMoveEvent 232 210 0 0 0 0 0\n"
"MouseMoveEvent 226 210 0 0 0 0 0\n"
"MouseMoveEvent 222 211 0 0 0 0 0\n"
"MouseMoveEvent 220 211 0 0 0 0 0\n"
"MouseMoveEvent 219 212 0 0 0 0 0\n"
"MouseMoveEvent 216 212 0 0 0 0 0\n"
"MouseMoveEvent 215 213 0 0 0 0 0\n"
"MouseMoveEvent 213 213 0 0 0 0 0\n"
"MouseMoveEvent 211 214 0 0 0 0 0\n"
"MouseMoveEvent 210 214 0 0 0 0 0\n"
"MouseMoveEvent 207 216 0 0 0 0 0\n"
"MouseMoveEvent 206 217 0 0 0 0 0\n"
"MouseMoveEvent 205 218 0 0 0 0 0\n"
"MouseMoveEvent 203 220 0 0 0 0 0\n"
"MouseMoveEvent 200 222 0 0 0 0 0\n"
"MouseMoveEvent 197 224 0 0 0 0 0\n"
"MouseMoveEvent 194 226 0 0 0 0 0\n"
"MouseMoveEvent 193 227 0 0 0 0 0\n"
"MouseMoveEvent 191 228 0 0 0 0 0\n"
"MouseMoveEvent 190 229 0 0 0 0 0\n"
"MouseMoveEvent 188 231 0 0 0 0 0\n"
"MouseMoveEvent 187 232 0 0 0 0 0\n"
"MouseMoveEvent 186 233 0 0 0 0 0\n"
"MouseMoveEvent 185 234 0 0 0 0 0\n"
"MouseMoveEvent 184 235 0 0 0 0 0\n"
"MouseMoveEvent 184 236 0 0 0 0 0\n"
"MouseMoveEvent 183 237 0 0 0 0 0\n"
"MouseMoveEvent 182 238 0 0 0 0 0\n"
"MouseMoveEvent 181 239 0 0 0 0 0\n"
"MouseMoveEvent 179 240 0 0 0 0 0\n"
"MouseMoveEvent 176 240 0 0 0 0 0\n"
"MouseMoveEvent 174 241 0 0 0 0 0\n"
"MouseMoveEvent 172 241 0 0 0 0 0\n"
"MouseMoveEvent 170 242 0 0 0 0 0\n"
"MouseMoveEvent 168 242 0 0 0 0 0\n"
"MouseMoveEvent 166 242 0 0 0 0 0\n"
"MouseMoveEvent 165 242 0 0 0 0 0\n"
"MouseMoveEvent 164 242 0 0 0 0 0\n"
"MouseMoveEvent 160 242 0 0 0 0 0\n"
"MouseMoveEvent 156 242 0 0 0 0 0\n"
"MouseMoveEvent 153 242 0 0 0 0 0\n"
"MouseMoveEvent 150 242 0 0 0 0 0\n"
"MouseMoveEvent 148 242 0 0 0 0 0\n"
"MouseMoveEvent 147 242 0 0 0 0 0\n"
"MouseMoveEvent 146 242 0 0 0 0 0\n"
"MouseMoveEvent 144 242 0 0 0 0 0\n"
"MouseMoveEvent 143 242 0 0 0 0 0\n"
"MouseMoveEvent 142 242 0 0 0 0 0\n"
"MouseMoveEvent 141 242 0 0 0 0 0\n"
"MouseMoveEvent 140 242 0 0 0 0 0\n"
"MouseMoveEvent 139 242 0 0 0 0 0\n"
"MouseMoveEvent 138 242 0 0 0 0 0\n"
"MouseMoveEvent 137 242 0 0 0 0 0\n"
"LeftButtonPressEvent 137 242 0 0 0 0 0\n"
"StartInteractionEvent 137 242 0 0 0 0 0\n"
"TimerEvent 137 242 0 0 0 0 0\n"
"RenderEvent 137 242 0 0 0 0 0\n"
"TimerEvent 137 242 0 0 0 0 0\n"
"RenderEvent 137 242 0 0 0 0 0\n"
"TimerEvent 137 242 0 0 0 0 0\n"
"RenderEvent 137 242 0 0 0 0 0\n"
"TimerEvent 137 242 0 0 0 0 0\n"
"RenderEvent 137 242 0 0 0 0 0\n"
"TimerEvent 137 242 0 0 0 0 0\n"
"RenderEvent 137 242 0 0 0 0 0\n"
"TimerEvent 137 242 0 0 0 0 0\n"
"RenderEvent 137 242 0 0 0 0 0\n"
"TimerEvent 137 242 0 0 0 0 0\n"
"RenderEvent 137 242 0 0 0 0 0\n"
"TimerEvent 137 242 0 0 0 0 0\n"
"RenderEvent 137 242 0 0 0 0 0\n"
"TimerEvent 137 242 0 0 0 0 0\n"
"RenderEvent 137 242 0 0 0 0 0\n"
"TimerEvent 137 242 0 0 0 0 0\n"
"RenderEvent 137 242 0 0 0 0 0\n"
"TimerEvent 137 242 0 0 0 0 0\n"
"RenderEvent 137 242 0 0 0 0 0\n"
"TimerEvent 137 242 0 0 0 0 0\n"
"RenderEvent 137 242 0 0 0 0 0\n"
"TimerEvent 137 242 0 0 0 0 0\n"
"RenderEvent 137 242 0 0 0 0 0\n"
"MouseMoveEvent 136 241 0 0 0 0 0\n"
"InteractionEvent 136 241 0 0 0 0 0\n"
"TimerEvent 136 241 0 0 0 0 0\n"
"RenderEvent 136 241 0 0 0 0 0\n"
"MouseMoveEvent 136 240 0 0 0 0 0\n"
"InteractionEvent 136 240 0 0 0 0 0\n"
"MouseMoveEvent 136 239 0 0 0 0 0\n"
"InteractionEvent 136 239 0 0 0 0 0\n"
"TimerEvent 136 239 0 0 0 0 0\n"
"RenderEvent 136 239 0 0 0 0 0\n"
"MouseMoveEvent 136 238 0 0 0 0 0\n"
"InteractionEvent 136 238 0 0 0 0 0\n"
"MouseMoveEvent 136 237 0 0 0 0 0\n"
"InteractionEvent 136 237 0 0 0 0 0\n"
"TimerEvent 136 237 0 0 0 0 0\n"
"RenderEvent 136 237 0 0 0 0 0\n"
"MouseMoveEvent 136 236 0 0 0 0 0\n"
"InteractionEvent 136 236 0 0 0 0 0\n"
"MouseMoveEvent 136 235 0 0 0 0 0\n"
"InteractionEvent 136 235 0 0 0 0 0\n"
"TimerEvent 136 235 0 0 0 0 0\n"
"RenderEvent 136 235 0 0 0 0 0\n"
"MouseMoveEvent 136 234 0 0 0 0 0\n"
"InteractionEvent 136 234 0 0 0 0 0\n"
"TimerEvent 136 234 0 0 0 0 0\n"
"RenderEvent 136 234 0 0 0 0 0\n"
"MouseMoveEvent 136 233 0 0 0 0 0\n"
"InteractionEvent 136 233 0 0 0 0 0\n"
"MouseMoveEvent 136 232 0 0 0 0 0\n"
"InteractionEvent 136 232 0 0 0 0 0\n"
"TimerEvent 136 232 0 0 0 0 0\n"
"RenderEvent 136 232 0 0 0 0 0\n"
"MouseMoveEvent 136 231 0 0 0 0 0\n"
"InteractionEvent 136 231 0 0 0 0 0\n"
"MouseMoveEvent 136 230 0 0 0 0 0\n"
"InteractionEvent 136 230 0 0 0 0 0\n"
"TimerEvent 136 230 0 0 0 0 0\n"
"RenderEvent 136 230 0 0 0 0 0\n"
"TimerEvent 136 230 0 0 0 0 0\n"
"RenderEvent 136 230 0 0 0 0 0\n"
"TimerEvent 136 230 0 0 0 0 0\n"
"RenderEvent 136 230 0 0 0 0 0\n"
"TimerEvent 136 230 0 0 0 0 0\n"
"RenderEvent 136 230 0 0 0 0 0\n"
"TimerEvent 136 230 0 0 0 0 0\n"
"RenderEvent 136 230 0 0 0 0 0\n"
"TimerEvent 136 230 0 0 0 0 0\n"
"RenderEvent 136 230 0 0 0 0 0\n"
"TimerEvent 136 230 0 0 0 0 0\n"
"RenderEvent 136 230 0 0 0 0 0\n"
"LeftButtonReleaseEvent 136 230 0 0 0 0 0\n"
"EndInteractionEvent 136 230 0 0 0 0 0\n"
"RenderEvent 136 230 0 0 0 0 0\n"
"MouseMoveEvent 136 228 0 0 0 0 0\n"
"MouseMoveEvent 136 226 0 0 0 0 0\n"
"MouseMoveEvent 136 224 0 0 0 0 0\n"
"MouseMoveEvent 136 222 0 0 0 0 0\n"
"MouseMoveEvent 136 220 0 0 0 0 0\n"
"MouseMoveEvent 136 218 0 0 0 0 0\n"
"MouseMoveEvent 136 216 0 0 0 0 0\n"
"MouseMoveEvent 136 213 0 0 0 0 0\n"
"MouseMoveEvent 136 210 0 0 0 0 0\n"
"MouseMoveEvent 136 207 0 0 0 0 0\n"
"MouseMoveEvent 136 204 0 0 0 0 0\n"
"MouseMoveEvent 137 201 0 0 0 0 0\n"
"MouseMoveEvent 138 198 0 0 0 0 0\n"
"MouseMoveEvent 139 196 0 0 0 0 0\n"
"MouseMoveEvent 139 194 0 0 0 0 0\n"
"MouseMoveEvent 140 191 0 0 0 0 0\n"
"MouseMoveEvent 142 187 0 0 0 0 0\n"
"MouseMoveEvent 142 184 0 0 0 0 0\n"
"MouseMoveEvent 144 181 0 0 0 0 0\n"
"MouseMoveEvent 145 177 0 0 0 0 0\n"
"MouseMoveEvent 148 173 0 0 0 0 0\n"
"MouseMoveEvent 151 169 0 0 0 0 0\n"
"MouseMoveEvent 156 164 0 0 0 0 0\n"
"MouseMoveEvent 162 158 0 0 0 0 0\n"
"MouseMoveEvent 166 153 0 0 0 0 0\n"
"MouseMoveEvent 170 149 0 0 0 0 0\n"
"MouseMoveEvent 174 145 0 0 0 0 0\n"
"MouseMoveEvent 178 143 0 0 0 0 0\n"
"MouseMoveEvent 184 142 0 0 0 0 0\n"
"MouseMoveEvent 188 140 0 0 0 0 0\n"
"MouseMoveEvent 193 139 0 0 0 0 0\n"
"MouseMoveEvent 197 139 0 0 0 0 0\n"
"MouseMoveEvent 201 137 0 0 0 0 0\n"
"MouseMoveEvent 202 137 0 0 0 0 0\n"
"MouseMoveEvent 204 137 0 0 0 0 0\n"
"MouseMoveEvent 205 137 0 0 0 0 0\n"
"MouseMoveEvent 206 137 0 0 0 0 0\n"
"MouseMoveEvent 209 136 0 0 0 0 0\n"
"MouseMoveEvent 211 136 0 0 0 0 0\n"
"MouseMoveEvent 212 136 0 0 0 0 0\n"
"MouseMoveEvent 213 135 0 0 0 0 0\n"
"MouseMoveEvent 214 135 0 0 0 0 0\n"
"MouseMoveEvent 215 134 0 0 0 0 0\n"
"MouseMoveEvent 216 133 0 0 0 0 0\n"
"LeftButtonPressEvent 216 133 0 0 0 0 0\n"
"StartInteractionEvent 216 133 0 0 0 0 0\n"
"TimerEvent 216 133 0 0 0 0 0\n"
"RenderEvent 216 133 0 0 0 0 0\n"
"MouseMoveEvent 219 132 0 0 0 0 0\n"
"InteractionEvent 219 132 0 0 0 0 0\n"
"MouseMoveEvent 220 131 0 0 0 0 0\n"
"InteractionEvent 220 131 0 0 0 0 0\n"
"TimerEvent 220 131 0 0 0 0 0\n"
"RenderEvent 220 131 0 0 0 0 0\n"
"MouseMoveEvent 221 130 0 0 0 0 0\n"
"InteractionEvent 221 130 0 0 0 0 0\n"
"MouseMoveEvent 222 129 0 0 0 0 0\n"
"InteractionEvent 222 129 0 0 0 0 0\n"
"TimerEvent 222 129 0 0 0 0 0\n"
"RenderEvent 222 129 0 0 0 0 0\n"
"MouseMoveEvent 223 128 0 0 0 0 0\n"
"InteractionEvent 223 128 0 0 0 0 0\n"
"TimerEvent 223 128 0 0 0 0 0\n"
"RenderEvent 223 128 0 0 0 0 0\n"
"TimerEvent 223 128 0 0 0 0 0\n"
"RenderEvent 223 128 0 0 0 0 0\n"
"TimerEvent 223 128 0 0 0 0 0\n"
"RenderEvent 223 128 0 0 0 0 0\n"
"TimerEvent 223 128 0 0 0 0 0\n"
"RenderEvent 223 128 0 0 0 0 0\n"
"TimerEvent 223 128 0 0 0 0 0\n"
"RenderEvent 223 128 0 0 0 0 0\n"
"LeftButtonReleaseEvent 223 128 0 0 0 0 0\n"
"EndInteractionEvent 223 128 0 0 0 0 0\n"
"RenderEvent 223 128 0 0 0 0 0\n"
"MouseMoveEvent 224 126 0 0 0 0 0\n"
"MouseMoveEvent 225 125 0 0 0 0 0\n"
"MouseMoveEvent 226 123 0 0 0 0 0\n"
"MouseMoveEvent 227 122 0 0 0 0 0\n"
"MouseMoveEvent 228 121 0 0 0 0 0\n"
"MouseMoveEvent 229 120 0 0 0 0 0\n"
"MouseMoveEvent 230 119 0 0 0 0 0\n"
"MouseMoveEvent 231 118 0 0 0 0 0\n"
"MouseMoveEvent 232 117 0 0 0 0 0\n"
"MouseMoveEvent 233 116 0 0 0 0 0\n"
"MouseMoveEvent 233 115 0 0 0 0 0\n"
"MouseMoveEvent 234 114 0 0 0 0 0\n"
"MouseMoveEvent 234 113 0 0 0 0 0\n"
"MouseMoveEvent 234 112 0 0 0 0 0\n"
"MouseMoveEvent 234 111 0 0 0 0 0\n"
"MouseMoveEvent 234 110 0 0 0 0 0\n"
"MouseMoveEvent 233 108 0 0 0 0 0\n"
"MouseMoveEvent 231 107 0 0 0 0 0\n"
"MouseMoveEvent 229 106 0 0 0 0 0\n"
"MouseMoveEvent 226 105 0 0 0 0 0\n"
"MouseMoveEvent 223 105 0 0 0 0 0\n"
"MouseMoveEvent 220 104 0 0 0 0 0\n"
"MouseMoveEvent 216 103 0 0 0 0 0\n"
"MouseMoveEvent 209 101 0 0 0 0 0\n"
"MouseMoveEvent 202 99 0 0 0 0 0\n"
"MouseMoveEvent 195 98 0 0 0 0 0\n"
"MouseMoveEvent 188 96 0 0 0 0 0\n"
"MouseMoveEvent 179 94 0 0 0 0 0\n"
"MouseMoveEvent 168 93 0 0 0 0 0\n"
"MouseMoveEvent 156 91 0 0 0 0 0\n"
"MouseMoveEvent 144 89 0 0 0 0 0\n"
"MouseMoveEvent 135 87 0 0 0 0 0\n"
"MouseMoveEvent 127 86 0 0 0 0 0\n"
"MouseMoveEvent 120 86 0 0 0 0 0\n"
"MouseMoveEvent 116 84 0 0 0 0 0\n"
"MouseMoveEvent 115 84 0 0 0 0 0\n"
"MouseMoveEvent 114 83 0 0 0 0 0\n"
"LeftButtonPressEvent 114 83 0 0 0 0 0\n"
"StartInteractionEvent 114 83 0 0 0 0 0\n"
"TimerEvent 114 83 0 0 0 0 0\n"
"RenderEvent 114 83 0 0 0 0 0\n"
"MouseMoveEvent 108 82 0 0 0 0 0\n"
"InteractionEvent 108 82 0 0 0 0 0\n"
"TimerEvent 108 82 0 0 0 0 0\n"
"RenderEvent 108 82 0 0 0 0 0\n"
"MouseMoveEvent 104 81 0 0 0 0 0\n"
"InteractionEvent 104 81 0 0 0 0 0\n"
"MouseMoveEvent 102 81 0 0 0 0 0\n"
"InteractionEvent 102 81 0 0 0 0 0\n"
"TimerEvent 102 81 0 0 0 0 0\n"
"RenderEvent 102 81 0 0 0 0 0\n"
"MouseMoveEvent 95 81 0 0 0 0 0\n"
"InteractionEvent 95 81 0 0 0 0 0\n"
"MouseMoveEvent 92 81 0 0 0 0 0\n"
"InteractionEvent 92 81 0 0 0 0 0\n"
"TimerEvent 92 81 0 0 0 0 0\n"
"RenderEvent 92 81 0 0 0 0 0\n"
"MouseMoveEvent 86 81 0 0 0 0 0\n"
"InteractionEvent 86 81 0 0 0 0 0\n"
"MouseMoveEvent 83 81 0 0 0 0 0\n"
"InteractionEvent 83 81 0 0 0 0 0\n"
"TimerEvent 83 81 0 0 0 0 0\n"
"RenderEvent 83 81 0 0 0 0 0\n"
"MouseMoveEvent 77 81 0 0 0 0 0\n"
"InteractionEvent 77 81 0 0 0 0 0\n"
"MouseMoveEvent 75 80 0 0 0 0 0\n"
"InteractionEvent 75 80 0 0 0 0 0\n"
"TimerEvent 75 80 0 0 0 0 0\n"
"RenderEvent 75 80 0 0 0 0 0\n"
"MouseMoveEvent 72 80 0 0 0 0 0\n"
"InteractionEvent 72 80 0 0 0 0 0\n"
"TimerEvent 72 80 0 0 0 0 0\n"
"RenderEvent 72 80 0 0 0 0 0\n"
"TimerEvent 72 80 0 0 0 0 0\n"
"RenderEvent 72 80 0 0 0 0 0\n"
"TimerEvent 72 80 0 0 0 0 0\n"
"RenderEvent 72 80 0 0 0 0 0\n"
"TimerEvent 72 80 0 0 0 0 0\n"
"RenderEvent 72 80 0 0 0 0 0\n"
"TimerEvent 72 80 0 0 0 0 0\n"
"RenderEvent 72 80 0 0 0 0 0\n"
"TimerEvent 72 80 0 0 0 0 0\n"
"RenderEvent 72 80 0 0 0 0 0\n"
"TimerEvent 72 80 0 0 0 0 0\n"
"RenderEvent 72 80 0 0 0 0 0\n"
"TimerEvent 72 80 0 0 0 0 0\n"
"RenderEvent 72 80 0 0 0 0 0\n"
"TimerEvent 72 80 0 0 0 0 0\n"
"RenderEvent 72 80 0 0 0 0 0\n"
"TimerEvent 72 80 0 0 0 0 0\n"
"RenderEvent 72 80 0 0 0 0 0\n"
"MouseMoveEvent 71 79 0 0 0 0 0\n"
"InteractionEvent 71 79 0 0 0 0 0\n"
"MouseMoveEvent 71 78 0 0 0 0 0\n"
"InteractionEvent 71 78 0 0 0 0 0\n"
"TimerEvent 71 78 0 0 0 0 0\n"
"RenderEvent 71 78 0 0 0 0 0\n"
"MouseMoveEvent 70 74 0 0 0 0 0\n"
"InteractionEvent 70 74 0 0 0 0 0\n"
"MouseMoveEvent 70 73 0 0 0 0 0\n"
"InteractionEvent 70 73 0 0 0 0 0\n"
"TimerEvent 70 73 0 0 0 0 0\n"
"RenderEvent 70 73 0 0 0 0 0\n"
"MouseMoveEvent 70 71 0 0 0 0 0\n"
"InteractionEvent 70 71 0 0 0 0 0\n"
"MouseMoveEvent 70 70 0 0 0 0 0\n"
"InteractionEvent 70 70 0 0 0 0 0\n"
"TimerEvent 70 70 0 0 0 0 0\n"
"RenderEvent 70 70 0 0 0 0 0\n"
"MouseMoveEvent 70 64 0 0 0 0 0\n"
"InteractionEvent 70 64 0 0 0 0 0\n"
"MouseMoveEvent 70 63 0 0 0 0 0\n"
"InteractionEvent 70 63 0 0 0 0 0\n"
"TimerEvent 70 63 0 0 0 0 0\n"
"RenderEvent 70 63 0 0 0 0 0\n"
"MouseMoveEvent 72 59 0 0 0 0 0\n"
"InteractionEvent 72 59 0 0 0 0 0\n"
"MouseMoveEvent 73 58 0 0 0 0 0\n"
"InteractionEvent 73 58 0 0 0 0 0\n"
"TimerEvent 73 58 0 0 0 0 0\n"
"RenderEvent 73 58 0 0 0 0 0\n"
"MouseMoveEvent 77 52 0 0 0 0 0\n"
"InteractionEvent 77 52 0 0 0 0 0\n"
"MouseMoveEvent 78 51 0 0 0 0 0\n"
"InteractionEvent 78 51 0 0 0 0 0\n"
"TimerEvent 78 51 0 0 0 0 0\n"
"RenderEvent 78 51 0 0 0 0 0\n"
"MouseMoveEvent 83 44 0 0 0 0 0\n"
"InteractionEvent 83 44 0 0 0 0 0\n"
"MouseMoveEvent 85 42 0 0 0 0 0\n"
"InteractionEvent 85 42 0 0 0 0 0\n"
"MouseMoveEvent 86 41 0 0 0 0 0\n"
"InteractionEvent 86 41 0 0 0 0 0\n"
"TimerEvent 86 41 0 0 0 0 0\n"
"RenderEvent 86 41 0 0 0 0 0\n"
"MouseMoveEvent 89 38 0 0 0 0 0\n"
"InteractionEvent 89 38 0 0 0 0 0\n"
"MouseMoveEvent 90 37 0 0 0 0 0\n"
"InteractionEvent 90 37 0 0 0 0 0\n"
"TimerEvent 90 37 0 0 0 0 0\n"
"RenderEvent 90 37 0 0 0 0 0\n"
"MouseMoveEvent 94 33 0 0 0 0 0\n"
"InteractionEvent 94 33 0 0 0 0 0\n"
"MouseMoveEvent 95 32 0 0 0 0 0\n"
"InteractionEvent 95 32 0 0 0 0 0\n"
"TimerEvent 95 32 0 0 0 0 0\n"
"RenderEvent 95 32 0 0 0 0 0\n"
"MouseMoveEvent 99 30 0 0 0 0 0\n"
"InteractionEvent 99 30 0 0 0 0 0\n"
"MouseMoveEvent 101 29 0 0 0 0 0\n"
"InteractionEvent 101 29 0 0 0 0 0\n"
"TimerEvent 101 29 0 0 0 0 0\n"
"RenderEvent 101 29 0 0 0 0 0\n"
"MouseMoveEvent 108 25 0 0 0 0 0\n"
"InteractionEvent 108 25 0 0 0 0 0\n"
"TimerEvent 108 25 0 0 0 0 0\n"
"RenderEvent 108 25 0 0 0 0 0\n"
"MouseMoveEvent 111 23 0 0 0 0 0\n"
"InteractionEvent 111 23 0 0 0 0 0\n"
"TimerEvent 111 23 0 0 0 0 0\n"
"RenderEvent 111 23 0 0 0 0 0\n"
"MouseMoveEvent 115 21 0 0 0 0 0\n"
"InteractionEvent 115 21 0 0 0 0 0\n"
"TimerEvent 115 21 0 0 0 0 0\n"
"RenderEvent 115 21 0 0 0 0 0\n"
"MouseMoveEvent 118 19 0 0 0 0 0\n"
"InteractionEvent 118 19 0 0 0 0 0\n"
"TimerEvent 118 19 0 0 0 0 0\n"
"RenderEvent 118 19 0 0 0 0 0\n"
"MouseMoveEvent 122 18 0 0 0 0 0\n"
"InteractionEvent 122 18 0 0 0 0 0\n"
"TimerEvent 122 18 0 0 0 0 0\n"
"RenderEvent 122 18 0 0 0 0 0\n"
"MouseMoveEvent 127 16 0 0 0 0 0\n"
"InteractionEvent 127 16 0 0 0 0 0\n"
"MouseMoveEvent 128 15 0 0 0 0 0\n"
"InteractionEvent 128 15 0 0 0 0 0\n"
"TimerEvent 128 15 0 0 0 0 0\n"
"RenderEvent 128 15 0 0 0 0 0\n"
"MouseMoveEvent 133 13 0 0 0 0 0\n"
"InteractionEvent 133 13 0 0 0 0 0\n"
"TimerEvent 133 13 0 0 0 0 0\n"
"RenderEvent 133 13 0 0 0 0 0\n"
"MouseMoveEvent 139 11 0 0 0 0 0\n"
"InteractionEvent 139 11 0 0 0 0 0\n"
"MouseMoveEvent 140 11 0 0 0 0 0\n"
"InteractionEvent 140 11 0 0 0 0 0\n"
"TimerEvent 140 11 0 0 0 0 0\n"
"RenderEvent 140 11 0 0 0 0 0\n"
"MouseMoveEvent 144 10 0 0 0 0 0\n"
"InteractionEvent 144 10 0 0 0 0 0\n"
"MouseMoveEvent 145 9 0 0 0 0 0\n"
"InteractionEvent 145 9 0 0 0 0 0\n"
"TimerEvent 145 9 0 0 0 0 0\n"
"RenderEvent 145 9 0 0 0 0 0\n"
"MouseMoveEvent 147 8 0 0 0 0 0\n"
"InteractionEvent 147 8 0 0 0 0 0\n"
"TimerEvent 147 8 0 0 0 0 0\n"
"RenderEvent 147 8 0 0 0 0 0\n"
"MouseMoveEvent 150 7 0 0 0 0 0\n"
"InteractionEvent 150 7 0 0 0 0 0\n"
"MouseMoveEvent 151 7 0 0 0 0 0\n"
"InteractionEvent 151 7 0 0 0 0 0\n"
"MouseMoveEvent 154 6 0 0 0 0 0\n"
"InteractionEvent 154 6 0 0 0 0 0\n"
"TimerEvent 154 6 0 0 0 0 0\n"
"RenderEvent 154 6 0 0 0 0 0\n"
"MouseMoveEvent 156 6 0 0 0 0 0\n"
"InteractionEvent 156 6 0 0 0 0 0\n"
"MouseMoveEvent 158 5 0 0 0 0 0\n"
"InteractionEvent 158 5 0 0 0 0 0\n"
"TimerEvent 158 5 0 0 0 0 0\n"
"RenderEvent 158 5 0 0 0 0 0\n"
"MouseMoveEvent 160 4 0 0 0 0 0\n"
"InteractionEvent 160 4 0 0 0 0 0\n"
"TimerEvent 160 4 0 0 0 0 0\n"
"RenderEvent 160 4 0 0 0 0 0\n"
"TimerEvent 160 4 0 0 0 0 0\n"
"RenderEvent 160 4 0 0 0 0 0\n"
"MouseMoveEvent 162 3 0 0 0 0 0\n"
"InteractionEvent 162 3 0 0 0 0 0\n"
"MouseMoveEvent 164 2 0 0 0 0 0\n"
"InteractionEvent 164 2 0 0 0 0 0\n"
"TimerEvent 164 2 0 0 0 0 0\n"
"RenderEvent 164 2 0 0 0 0 0\n"
"MouseMoveEvent 167 1 0 0 0 0 0\n"
"InteractionEvent 167 1 0 0 0 0 0\n"
"TimerEvent 167 1 0 0 0 0 0\n"
"RenderEvent 167 1 0 0 0 0 0\n"
"MouseMoveEvent 171 -1 0 0 0 0 0\n"
"InteractionEvent 171 -1 0 0 0 0 0\n"
"LeaveEvent 171 -1 0 0 0 0 0\n"
"MouseMoveEvent 171 -1 0 0 0 0 0\n"
"InteractionEvent 171 -1 0 0 0 0 0\n"
"TimerEvent 171 -1 0 0 0 0 0\n"
"RenderEvent 171 -1 0 0 0 0 0\n"
"TimerEvent 171 -1 0 0 0 0 0\n"
"RenderEvent 171 -1 0 0 0 0 0\n"
"TimerEvent 171 -1 0 0 0 0 0\n"
"RenderEvent 171 -1 0 0 0 0 0\n"
"LeftButtonReleaseEvent 171 -1 0 0 0 0 0\n"
"EndInteractionEvent 171 -1 0 0 0 0 0\n"
"RenderEvent 171 -1 0 0 0 0 0\n"
"LeaveEvent 171 -1 0 0 0 0 0\n"
"EnterEvent 174 0 0 0 0 0 0\n"
"MouseMoveEvent 174 0 0 0 0 0 0\n"
"MouseMoveEvent 175 1 0 0 0 0 0\n"
"MouseMoveEvent 175 2 0 0 0 0 0\n"
"MouseMoveEvent 175 4 0 0 0 0 0\n"
"MouseMoveEvent 175 6 0 0 0 0 0\n"
"MouseMoveEvent 175 8 0 0 0 0 0\n"
"MouseMoveEvent 175 10 0 0 0 0 0\n"
"MouseMoveEvent 175 12 0 0 0 0 0\n"
"MouseMoveEvent 175 15 0 0 0 0 0\n"
"MouseMoveEvent 175 18 0 0 0 0 0\n"
"MouseMoveEvent 175 21 0 0 0 0 0\n"
"MouseMoveEvent 176 23 0 0 0 0 0\n"
"MouseMoveEvent 178 27 0 0 0 0 0\n"
"MouseMoveEvent 180 29 0 0 0 0 0\n"
"MouseMoveEvent 188 33 0 0 0 0 0\n"
"MouseMoveEvent 198 34 0 0 0 0 0\n"
"MouseMoveEvent 207 36 0 0 0 0 0\n"
"MouseMoveEvent 221 36 0 0 0 0 0\n"
"MouseMoveEvent 238 36 0 0 0 0 0\n"
"MouseMoveEvent 255 36 0 0 0 0 0\n"
"MouseMoveEvent 272 36 0 0 0 0 0\n"
"MouseMoveEvent 289 36 0 0 0 0 0\n"
"LeaveEvent 306 36 0 0 0 0 0\n"
;

int TestGPURayCastTwoComponentsGradient(int argc, char *argv[])
{
  cout << "CTEST_FULL_OUTPUT (Avoid ctest truncation of output)" << endl;

  int dims[3] = { 35, 35, 35 };

  // Create a vtkImageData with two components
  vtkNew<vtkImageData> image;
  image->SetDimensions(dims[0], dims[1], dims[2]);
  image->AllocateScalars(VTK_DOUBLE, 2);

  // Fill the first half rectangular parallelopiped along X with the
  // first component values and the second half with second component values
  double * ptr = static_cast<double *> (image->GetScalarPointer(0, 0, 0));

  for (int z = 0; z < dims[2]; ++z)
  {
    for (int y = 0; y < dims[1]; ++y)
    {
      for (int x = 0; x < dims[0]; ++x)
      {
        if (x < dims[0] / 2)
        {
          *ptr++ = 0.0;
          *ptr++ = 0.0;
        }
        else
        {
          *ptr++ = 1.0;
          *ptr++ = 1.0;
        }
      }
    }
  }

  vtkNew<vtkRenderWindow> renWin;
  renWin->SetSize(301, 300); // Intentional NPOT size
  renWin->SetMultiSamples(0);

  vtkNew<vtkRenderer> ren;
  renWin->AddRenderer(ren.GetPointer());

  vtkNew<vtkRenderWindowInteractor> iren;
  vtkNew<vtkInteractorStyleTrackballCamera> style;
  iren->SetInteractorStyle(style.GetPointer());
  iren->SetRenderWindow(renWin.GetPointer());

  renWin->Render();

  // Volume render the dataset
  vtkNew<vtkGPUVolumeRayCastMapper> mapper;
  mapper->AutoAdjustSampleDistancesOff();
  mapper->SetSampleDistance(0.9);
  mapper->SetInputData(image.GetPointer());

  // Color transfer function
  vtkNew<vtkColorTransferFunction> ctf1;
  ctf1->AddRGBPoint(0.0, 0.0, 0.0, 0.0);
  ctf1->AddRGBPoint(1.0, 1.0, 0.0, 0.0);

  vtkNew<vtkColorTransferFunction> ctf2;
  ctf2->AddRGBPoint(0.0, 0.0, 0.0, 0.0);
  ctf2->AddRGBPoint(1.0, 0.0, 0.0, 1.0);

  // Opacity functions
  vtkNew<vtkPiecewiseFunction> pf1;
  pf1->AddPoint(0.0, 0.0);
  pf1->AddPoint(1.0, 0.5);

  vtkNew<vtkPiecewiseFunction> pf2;
  pf2->AddPoint(0.0, 0.0);
  pf2->AddPoint(1.0, 0.5);

  // Gradient Opacity function
  vtkNew<vtkPiecewiseFunction> pf3;
  pf3->AddPoint(0.0, 0.0);
  pf3->AddPoint(1.0, 0.5);

  vtkNew<vtkPiecewiseFunction> pf4;
  pf4->AddPoint(0.0, 0.0);
  pf4->AddPoint(1.0, 0.5);

  // Volume property with independent components ON
  vtkNew<vtkVolumeProperty> property;
  property->IndependentComponentsOn();

  // Set color and opacity functions
  property->SetColor(0, ctf1.GetPointer());
  property->SetColor(1, ctf2.GetPointer());
  property->SetScalarOpacity(0, pf1.GetPointer());
  property->SetScalarOpacity(1, pf2.GetPointer());
  property->SetGradientOpacity(0, pf3.GetPointer());
  property->SetGradientOpacity(1, pf4.GetPointer());

  vtkNew<vtkVolume> volume;
  volume->SetMapper(mapper.GetPointer());
  volume->SetProperty(property.GetPointer());
  ren->AddVolume(volume.GetPointer());

  ren->ResetCamera();

  iren->Initialize();
  renWin->Render();

  return vtkTesting::InteractorEventLoop(argc, argv,
    iren.GetPointer(),
    TestGPURayCastTwoComponentsIndependentLog);
}
