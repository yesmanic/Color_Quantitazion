# Color Quantitazion
Color quantization is a command-line utility for reduce the number of color of a PNG image. It's written in and requires a C compiler to build.

## Installation
To install Color Quantization run the following commands:

### Prerequisits
- git
- C compiler
- make
- libpng

```bash
git clone https://github.com/yesmanic/Color_Quantitazion
cd Color_Quantization
make
```

## Usage
To use Color Quantization run the following command:
```bash
./quantize filename colors [MAX_ITERATIONS]

positional arguments:
  filename      the name of the png file
  colors      number of colors

optional arguments:
  MAX_ITERATIONS        maximum number of iterations
```

## Examples
```bash
./quantize sky.png 80 50
```
## Contact
Yesman - yesman.choque@gmail.com

Project Link: https://github.com/yesmanic/Ignite_Lab

<p align="right">(<a href="#top">back to top</a>)</p>