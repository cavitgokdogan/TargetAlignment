# Target Detection
!!! You must have the OpenCV library for these codes to work

The imported image is converted to HSV format. Then, the color determination is made by entering the values in the HSV format of the red color and a small square is created in the center of the screen. After these operations are performed, operations are carried out to remove the noise in the detected image. In order to find the midpoint of the detected object and show this point, the x and y coordinates are taken and the area is calculated. The center point of the target is shown on the screen and the direction it needs to move to reach the center of the screen is printed on the screen.
