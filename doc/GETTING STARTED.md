# Getting Started



# Table of contents

- [Structure of Repository](#structure-of-repository)
- [Install ZjuMatrix](#install-zjumatrix)
  - [Setup your `GitHub` account](#setup-your-github-account)
  - [Get `ZjuMatrix`](#get-zjumatrix)
  - [Configure and Generate `ZjuMatrix`](#configure-and-generate-zjumatrix)
- [Usage of ZjuMatrix](#usage-of-zjumatrix)



## Structure of Repository

- **`ZjuMatrix/`** contains the source files and head files of the library. 
- **`doc/`** contains documentation of the library.
- **`examples/`** contains two examples of the library.
- **`tests/`** contains testing files of  the library.
- **`CMakeLists.txt`** provides `cmake` commands for constructing the project.
- **`LICENSE.md`** provides MIT license for the library.
- **`README.md`** gives brief introduction of the library. 

The structure tree of `ZjuMatrix` project is shown as follows: 

```cmd
├─ZjuMatrix
│  ├─ZjuMatrix.h
│  ├─ZjuMatrix.cpp
│  ├─XVector.h
│  ├─XVector.cpp
│  ├─XPVector.h
│  ├─XPVector.cpp
│  ├─XList.h
│  ├─XList.cpp
│  ├─XDoubleMatrix.h
│  ├─XDoubleMatrix.cpp
│  ├─XSquareDoubleMatrix.h
│  ├─XSquareDoubleMatrix.cpp
│  ├─XSymDoubleMatrix.h
│  ├─XSymDoubleMatrix.cpp
│  ├─XBandDoubleMatrix.h
│  └─XBandDoubleMatrix.cpp
├─README.md
├─LINCENSE.md
├─doc
│  ├─html
│  │  └─index.html
│  ├─AUTHOR.md
│  ├─EXAMPLES.md
│  └─GETTING STARTED.md
├─examples
│  ├─exampleOne
│  │  ├─examOne_f.txt
│  │  ├─examOne_gK.txt
│  │  └─ZjuMatrixExampleOne.cpp
│  └─exampleTwo
│     ├─ExamTwo_gK.txt
│     ├─ExamTwo_gM.txt
│     └─ZjuMatrixExampleTwo.cpp
├─tests
│  └─ZjuMatrixTest.cpp
└─assets
   ├─Example1.png
   └─Example2.png
```



## Install `ZjuMatrix`

### Setup your `GitHub` account

Configure `git` with your name and email address: 

```git
$ git config --global user.name "Your name"
$ git config --global user.email "youtEmail@address.com"
```

### Get `ZjuMatrix`

```git
$ git clone --recursive git@github.com:/xxxx/xxxx.git
```

### Configure and Generate `ZjuMatrix`

First, create a `build` folder in `ZjuMatrix-main` folder and enter it: 

```cmd
cd path/to/ZjuMatrix-main
mkdir build
cd build
```

In Linux or Windows with MinGW-W64, please run `ZjuMatrix` configuration with `cmake ..` and compile with `make -j<N>`, where `N` is the desired number of processes. 

Otherwise, the recommand generator for ZjuMatrix is "Visual Studio 16 2019"，as ZjuMatrix was developed in this environment. Therefore, if the current generator is not the same as the recommand generator, you can altinatively choose to configure `ZjuMatrix` with

```cmake
cmake -G "Visual Studio 16 2019" ..
```

And the complication will be done in Visual Studio 2019 and the ZjuMatrix.lib will then be obtained.

 

## Usage of `ZjuMatrix`

`ZjuMatrix` is designed for finite element method. Both static and dynamic analysis of finite element problem are taken as examples to illustrate how `ZjuMatrix` accomplishes underlying support for finite element method. Source files and data files can be found in the path of `examples/`. 

The first example is about structural static analysis, and the second one is about structural dynamic analysis. For more details, please click: [Examples](EXAMPLES.md). 

And the documentation is provided here: [Documentation](html/index.html).

