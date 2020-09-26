# ObjectTracking  
&emsp;
## Colored Object Detection 
&emsp;

透過的簡易的方法（色彩空間轉換操作、與mask做and運算、去雜訊）達到偵測影片中特定色彩的物體。 &emsp;

### demo 
&emsp;
![image](https://github.com/sfwang20/ObjectTracking/blob/master/demo/ColorObjDetect.gif) &emsp;

## Lucas-Kanade algorithm   
&emsp;
使用電腦視覺中廣泛使用的Lucas-Kanade algorithm實現光流追蹤  &emsp;

Lucas-Kanade algorithm：[An Iterative Image Registration Technique with an Application to Stereo Vision](http://cseweb.ucsd.edu/classes/sp02/cse252/lucaskanade81.pdf) &emsp;  

### demo  
&emsp;

![image](https://github.com/sfwang20/ObjectTracking/blob/master/demo/tracking_airplane.gif)  &emsp;
  
  
## Corners detection and tracking 
&emsp;

### goodFeaturesTrack v.s corner Harris track 
&emsp;

Shi-Tomasi algorithm：[Good Features to Track](http://www.ai.mit.edu/courses/6.891/handouts/shi94good.pdf)   &emsp;

Harris corner detection：[A COMBINED CORNER AND EDGE DETECTOR](http://www.bmva.org/bmvc/1988/avc-88-023.pdf)  &emsp;

### demo  
&emsp;

![image](https://github.com/sfwang20/ObjectTracking/blob/master/demo/comparsion.gif)  &emsp;

比較Shi-Tomasi algorithm(左)及Harris corner detection(右)二方法檢測影片中角點之效果  &emsp;
&emsp;

![image](https://github.com/sfwang20/ObjectTracking/blob/master/demo/comparsion.png)  &emsp;
  

![image](https://github.com/sfwang20/ObjectTracking/blob/master/demo/comparsion2.png)  &emsp;

Shi-Tomasi algorithm增加檢測的細節，在精確度上有一定的提升，同時並可更好的控制檢測到角點的特性，例如角點之間的最小距離、依據特徵值顯示的角點個數等。




