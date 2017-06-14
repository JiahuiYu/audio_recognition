Music/Audio Fingerprinting and Recognition Application in C++
===============================================

- Youtube demo [Here](https://www.youtube.com/watch?v=tvoyZkcDKiw).


Features:
-----

- audio Fingerprinting and Recognition
- accuracy: 100% Accuracy of 500 6-second songs cuts in 100 songs list
- efficiency: recognize in less than 0.1 second per song cut
- memory: 10000 songs database in 4G memory
- data Structure: support 2,500,000 songs and each song should be less than 7 minutes
- time point recognition: return the TIME POINT of the cut song in original song


Dependencies:
-----

- fftw3:
    Under Debian/Ubuntu, please run `apt-get install libfftw3-dev`.

Compile & Run:
-----

- extract songs to ./bin/ dir
- `make` to produce two excutive files in ./bin/ 
- the songs should be .wav format
- the songs should be contained in ./bin/samples/ 
- you may download the example songs
    link: http://pan.baidu.com/s/1ntsoIlr
    password: wgi7 
- run `cd bin`, `./build` and it'll produce a file called `database`
- run `./recog ${filename}` to recog the songs that in samples list

Limitations:
-----
   - bad code style
   - lack of documents
