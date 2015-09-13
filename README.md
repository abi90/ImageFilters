# ImageFilters
This project was a college assignment for the course of Programming Languages.
The goal of this project was to develop a parallel image processing framework.

Introduction: 
 Parallel computing refers to the simultaneous use of multiple compute resources to solve a computational problem. 
 In this assignment the tool used for parallelism was OpenMP. 
 OpenMP is an API that may be used to explicitly direct multi-threaded, shared memory parallelism. 
 
Overview: 
GUI: 
 The GUI of this assignment was developed in python. The modules names are pl.py and pl_support.py. 
 They were generated with PAGE (Python Automatic GUI Generator).  
  

FilterLibs.pyd: 
This module is the compiled version of imageFilters.cpp which allows python to call applyFilter( String path, int filter). 
The given image will be transformed in gray scale. 
Includes the openMP library and the opencv library. 
