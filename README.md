# Edge-Detection
This project is about detecting edges using canny edge detector.
The canny edge detector is implemented from scratch using c++.
Steps involved in creating a canny edge detector:
STEP 1: smoothen the image using gaussian blur.
STEP 2: Use differential operator to find the magnitude and direction of every edge pixel.
STEP 3: Non maximal supression or Thinning is done. Here the thick edges are supressed into thinner ones.
STEP 4: Hysteresis Thresholding: Two thresholds are selected. pixels lower than the lowT will become zero. pixels higher than the HighT will become one. The candidate pixels will become one if they can be linked to any one of the strong pixel.
