# ObjectTracking  

## Colored Object Detection
透過image transformation操作(color space、mask operation、blur）達到偵測影片中特定色彩的物體。 &emsp;

### demo
![image](https://github.com/sfwang20/ObjectTracking/blob/master/demo/ColorObjDetect.gif) &emsp;
&emsp;

## Lucas-Kanade algorithm
使用電腦視覺中廣泛使用的Lucas-Kanade algorithm實現光流追蹤  &emsp;

Lucas-Kanade algorithm：[An Iterative Image Registration Technique with an Application to Stereo Vision](http://cseweb.ucsd.edu/classes/sp02/cse252/lucaskanade81.pdf) &emsp;  

### demo 
![image](https://github.com/sfwang20/ObjectTracking/blob/master/demo/tracking_airplane.gif)
&emsp;

## Optical flow by Farneback algorithm
嘗試使用Farneback所提出的光流演算法
Farneback algorithm(1)：[Two-Frame Motion Estimation Based on Polynomial Expansion](https://www.diva-portal.org/smash/get/diva2:273847/FULLTEXT01.pdf)
Farneback algorithm(2)：[Polynomial expansion for orientation and motion estimation](http://www.diva-portal.org/smash/get/diva2:302485/FULLTEXT01.pdf)
&emsp;
### demo
![image](https://github.com/sfwang20/ObjectTracking/blob/master/demo/farneback.gif)
&emsp;

## Corners detection and tracking 

### goodFeaturesTrack v.s corner Harris track 

Shi-Tomasi algorithm：[Good Features to Track](http://www.ai.mit.edu/courses/6.891/handouts/shi94good.pdf)   &emsp;

Harris corner detection：[A COMBINED CORNER AND EDGE DETECTOR](http://www.bmva.org/bmvc/1988/avc-88-023.pdf)  &emsp;

### demo  

![image](https://github.com/sfwang20/ObjectTracking/blob/master/demo/comparsion.gif)  &emsp;

比較Shi-Tomasi algorithm(左)及Harris corner detection(右)二方法檢測影片中角點之效果  &emsp;
&emsp;

![image](https://github.com/sfwang20/ObjectTracking/blob/master/demo/comparsion.png)  &emsp;
  

![image](https://github.com/sfwang20/ObjectTracking/blob/master/demo/comparsion2.png)  &emsp;

Shi-Tomasi algorithm增加檢測的細節，在精確度上有一定的提升，同時並可更好的控制檢測到角點的特性，例如角點之間的最小距離、依據特徵值顯示的角點個數等。




