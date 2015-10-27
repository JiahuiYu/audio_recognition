Music/Audio Recognition Application written in C++
===============================================

### Youtube Available Now! Click [Here](https://www.youtube.com/watch?v=tvoyZkcDKiw)

* I start this project to attend a COMPETITION. My partner and I finshed this project on Windows8 and won the *First Prize* delivered by [National Engineering Laboratory for Speech and Language Informatinon Processing](http://nelslip.ustc.edu.cn/html/yunews/detail_2014_05/30/191.shtml).
* Now it is successfully moved to LINUX (Ubuntu/Debian).
* Feel free to contact me yjh199511 at gmail. 2/4/2015

***

Features:
-----

    * Robust Audio Recognition
    * High Accuracy: 100% Accuracycy of 500 6-second songs cuts in 100 songs list.
    * High efficiency: recognize in less than 0.1 second per song.
    * Memory reduction: 4G is enough for 10000 songs.
    * Data Structure: support 2,500,000 songs and each song less than 7 minutes.
    * More feature: return the TIME POINT of the cut song in original song.

Dependencies:
-----

    * fftw3:
        If under Debian/Ubuntu, run `apt-get install libfftw3-dev`.

Compile & Run:
-----

    * extract songs to ./bin/ dir.
    * `make` to produce two excutive files in ./bin/ 
    * The songs should be .wav format.
    * The songs should be contained in ./bin/samples/ 
    * You may download the songs.
        link: http://pan.baidu.com/s/1ntsoIlr
        password: wgi7 
    * run `cd bin`, `./build` and it'll produce a file called `database`
    * run `./recog ${filename}` to recog the songs that in samples list.

TODO:
-----

   - More Documents and comments about the codes.

DONE:
-----

   - All the codes in Windows.
   - Transfer the codes from windows to linux.
   - Solve the BaiduMusic download tools to update new songs automatically.


[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/jh-yu/audiorecognition/trend.png)](https://bitdeli.com/free "Bitdeli Badge")
