# ZjuMatrix

![Static Badge](https://img.shields.io/badge/release-v1.0-blue)![Static Badge](https://img.shields.io/badge/License-MIT-blue) ![Static Badge](https://img.shields.io/badge/Documentation-Doxygen-blue)



# Table of contents

- [Introduction](#introduction)
- [Background](#background)
- [Getting Started](#getting-started)
- [Known Bugs and Upcoming Features](#known-bugs-and-upcoming-features)
- [License](#license)
- [Fundings](#funding)
- [Reference](#reference)



## Introduction

​        `ZjuMatirx` is a object-oriented C++ vector and matrix class  library designed for finite element analysis. It contains vector classes, matrix classes, and functions declared in `ZjuMatrix` head files. Its functions can be concluded as followings: data storage management, basic operations and computations of vectors and matrices, matrix factorizations, equation solving and eigenvalue problem solving. These functions provide sound and portable underlying support for finite element analysis. 

​        You can begin with the tutorials here: [Getting Started](doc/GETTING STARTED.md). Examples are provided in the `examples/` folder, and details are explained here: [Examples](doc/EXAMPLES.md).  For more detailed guidance of `ZjuMatrix`, please click here:  [Documentation](doc/html/index.html). 



## Background

​        Finite element analysis plays a vital role in the field of science and technology, offering valuable insights through the use of matrix operations, storage of large banded matrices, and solving algebraic equations and eigenvalue problems. LINPACK [[1]](https://netlib.org/linpack/) and EISPACK [[2]](#https://doi.org/10.1016/0010-4655(74)90086-1) are renowned software packages in linear algebra. While LINPACK focuses on solving linear algebraic equations, EISPACK addresses eigenvalue problems of matrices. Both packages rely on the BLAS [[3]](#https://dl.acm.org/doi/10.1145/355841.355847) library for fundamental vector and matrix operations. As the high-performance computing technology developed, LAPACK [[4]](#https://netlib.org/lapack/)  was written based on LINPACK and EISPACK. All the packages mentioned above were written in FORTRAN, and their functions contained almost all linear algebra and matrix eigenvalue problem. With the rise of object-oriented programming technology, LAPACK was rewritten by C++ language, known as LAPACK++ [[5]](#https://sourceforge.net/projects/lapackpp/). 

As functions continuously increased, software packages mentioned above gradually expanded. Nowadays, LAPACK has grown to encompass over 1000 subroutines, comprising more than 600,000 FORTRAN statements. However, the complexity of LAPACK makes them less user-friendly for users with limited knowledge of the underlying theory. To address this, Professor Moler created MATLAB [[6]](#https://matlab.mathworks.com/) based on these packages, leading to the establishment of MathWorks® company, which achieved tremendous success. Octave [[7]](#https://octave.org/), an open-source software alternative to MATLAB, also provides solutions for linear algebraic equations and matrix eigenvalue problems. Numpy [[8]](#https://numpy.org/), a package built on the popular Python [[9]](#https://www.python.org/)] language, offers similar functionality.

These software packages and commercial solutions provide powerful matrix computation capabilities. Moreover, MATLAB, Octave, and Python have evolved into fully-fledged programming languages, allowing for further customization and specialization, as evidenced by various software built on MATLAB and Python [[10-15]](#reference). However, code written in MATLAB or Python is inherently slower and less efficient due to their nature as scripting languages. Additionally, utilizing these languages necessitates the installation of their respective programming environments. In the context of a specific professional software application that does not require the full range of MATLAB or Python features, such inefficiencies can hinder performance.

Furthermore, existing software packages and commercial solutions fail to fully exploit the unique properties of matrices encountered in finite element analysis, such as the symmetry and positive-definiteness of banded matrices. Specialized algorithms suitable for static analysis and free vibration problems using finite element method, such as the conjugate gradient method and subspace iteration method, are also absent. With the advancement of digitalization in various industries, finite element analysis (FEA) has widespread applications as a fundamental tool. However, existing commercial FEA software packages are standalone and cannot be integrated into digital software used in different industries. Therefore, it is necessary to develop these fundamental tools and expand the application scenarios of the finite element method. 

To address these limitations, we propose the use of object-oriented technology and the C++ programming language to develop ZjuMatrix. ZjuMatrix implements vector and matrix classes, providing efficient data storage management for finite element analysis programs. The library defines classes for general, square, symmetric, and symmetric banded matrices. It includes basic matrix operations such as addition, subtraction, and multiplication, as well as more complex computations like LU factorization of a square matrix, LDL factorization of a symmetric positive definite matrix, determinant calculation, matrix inversion, eigen pair calculation for symmetric matrices, and computation of generalized eigenvalue problems for symmetric banded matrices. ZjuMatrix serves as a fundamental framework supporting the implementation of the finite element method. It can be concluded that ZjuMatrix offers a streamlined and efficient solution tailored specifically for finite element analysis, leveraging object-oriented technology and the power of C++.



## Getting Started

​        Please begin with the tutorials here: [Getting Started](doc/GETTING STARTED.md).

​        Examples are provided in the `examples/` folder, and details are explained here: [Examples](doc/EXAMPLES.md).

​        For more detailed guidance of `ZjuMatrix`, please click here:  [Documentation](doc/html/index.html). 



## Known Bugs and Upcoming Features

​        Please send bug reports and feature requests via [issue tracker]() on GitHub. 



## License

​        The license of `ZjuMatrix`  is MIT, please click here for more information: [License](LICENSE.md).



 ## Funding

​       This work was supported by the “Pioneer” and “Leading Goose” R & D Program of Zhejiang Province (No. 2022C01143) and National Natural Science Foundation of China (Nos. 12272335 & 12072097).



## Reference

[1]   https://netlib.org/linpack/

[2]   Garbow BS. (1974). EISPACK - A package of matrix eigensystem routines. Computer Physics Communications. 7(4): 179–184. doi:10.1016/0010-4655(74)90086-1.

[3]   Lawson CL, Hanson RJ, Kincaid D, Krogh FT. (1979). Basic linear algebra subprograms for FORTRAN usage. ACM Transactions on Mathematical Software. 5(3): 308-323. doi: 10.1145/ 355841.355847.

[4]   https://netlib.org/lapack/

[5]   https://sourceforge.net/projects/lapackpp/

[6]   https://matlab.mathworks.com/

[7]   https://octave.org/

[8]   https://numpy.org/

[9]   https://www.python.org/

[10]  Liu GY, Hsiao JH, Zhou WD, Tian L. (2023). MartMi-BCI: A matlab-based real-time motor imagery brain-computer interface platform. SoftWareX. 22: 1-6. doi: 10.1016/j.softx.2023.101371. 

[11]  Bidegain G, Ben-Horin T, Powell EN, Klinck JM, Hofmann EE. (2023). MarineEpi: A GUI-based Matlab toolbox to simulate marine pathogen transmission. SoftWareX. 22: 1-7. doi: 10.1016/j.softx.2023.101357. 

[12]  Abi-Mansour A. (2019). PyGran: An object-oriented library for DEM simulation and analysis. SoftWareX. 9: 168-174. doi: 10.1016/j.softx.2019.01.016. 

[13]  Szatkowski M, Litwin P, Masajada J. (2023). LBSA: A GUI-based Matlab software for the advanced laser beam shaping with spatial light modulators. SoftWareX. 22: 1-6. doi: 10.1016/j.softx.2023.101342. 

[14]  D’Aquino Z, Arabas S, Curtis JH, Vaishnav A, Riemer N, West M. (2024). PyPartMC: A Pythonic interface to a paricle-resolved, Monte Carlo aerosol simulation framework. Software. 25: 1-8. doi: 10.1016/j.softx.2023.101613. 

[15]  Tsapetis D, Shields MD, Giovanis DG, Olivier A, Novak L, Chakroborty P, Sharma H, Chauhan M, Kontolati K, Vandanapu L, Loukrezis D, Gardner M. (2023). SoftWareX. 24: 1-7. doi: 10.1016/j.softx.2023.101561. 