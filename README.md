# Color Quantitazion
Color Quantization is a command-line utility for reducing the number of color of a PNG image. It's written in C and requires a C compiler to build.

## Installation
To install Color Quantization run the following commands:

### Prerequisits
- git
- C compiler
- make
- libpng

```bash
git clone https://github.com/yesmanic/Color_Quantization
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
./quantize sky.png 20 50
```

| Original | Output (20 colors) |
|---------|---------|
|![sky](https://user-images.githubusercontent.com/62268626/211026221-92680f05-4c62-4632-8217-d7036ee5d2f0.png)|![sky-20-50](https://user-images.githubusercontent.com/62268626/211026117-5197e007-32b4-4d61-9cf4-7d192afaf5e7.png)|

## Contact
Yesman - yesman.choque@gmail.com

Project Link: https://github.com/yesmanic/Color_Quantization

<p align="right">(<a href="#top">back to top</a>)</p>
