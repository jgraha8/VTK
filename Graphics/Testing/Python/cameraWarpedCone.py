#!/usr/bin/env python

import sys

for i in range(0, len(sys.argv)):
    if sys.argv[i] == '-A' and i < len(sys.argv)-1:
        sys.path = sys.path + [sys.argv[i+1]]

import vtk
from vtk.util.misc import vtkRegressionTestImage

# create a rendering window and renderer
ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)
renWin.SetSize(300,300)

# create an actor and give it cone geometry
cone = vtk.vtkConeSource()
cone.SetResolution(8)
coneMapper = vtk.vtkPolyDataMapper()
coneMapper.SetInput(cone.GetOutput())
coneActor = vtk.vtkActor()
coneActor.SetMapper(coneMapper)

# create a transform and distort the camera using it
mat = vtk.vtkMatrix4x4()
mat.SetElement(0,0,0.5)
mat.SetElement(0,1,0)
mat.SetElement(0,2,0)
mat.SetElement(0,3,0)
mat.SetElement(1,0,0)
mat.SetElement(1,1,1)
mat.SetElement(1,2,0)
mat.SetElement(1,3,0)
mat.SetElement(2,0,0)
mat.SetElement(2,1,0)
mat.SetElement(2,2,1)
mat.SetElement(2,3,0)
mat.SetElement(3,0,0)
mat.SetElement(3,1,0)
mat.SetElement(3,2,0)
mat.SetElement(3,3,1)

trans = vtk.vtkTransform()
trans.SetMatrix(mat)

# assign our actor to the renderer
ren.AddActor(coneActor)

ren.ResetCamera();
ren.GetActiveCamera().SetUserTransform(trans); 

renWin.Render()
retVal = vtkRegressionTestImage(renWin)

sys.exit( not retVal )
