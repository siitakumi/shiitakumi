float margin = 100;
float xnoise, ynoise, znoise;
float xstart, ystart, zstart;
float seednoise, zoom;

void setup() {
  size(800, 800, P3D);
  frameRate(24);
  
  xstart = 0;
  ystart = 0;
  zstart = 0;
  seednoise = random(1);
  zoom = 0;
  
  noStroke();
}

void clearBackground() {
  background(0);
}

void draw() {
  clearBackground();
  
  seednoise += 0.01;
  if (zoom > -1600) { zoom -= 4; }
 
  translate(width/2, height/2, zoom);
  rotateY(frameCount * 0.02);
  rotateX(frameCount * 0.01);
  rotateZ(frameCount * 0.005);
  
  xstart = noise(seednoise) * 10;
  ystart = xstart;
  zstart = ystart;
  
  xnoise = xstart;
  float inc = 0.1;

  for (float i =- 900+margin; i <= 900-margin; i += margin){
    pushMatrix();
    xnoise += inc;
    ynoise = ystart;
    for (float j =- 900+margin; j <= 900-margin; j += margin){
      pushMatrix();
      ynoise += inc;
      znoise = zstart;
      for (float k =- 900+margin; k <= 900-margin; k += margin){
        pushMatrix();
        znoise += inc;
        
        float boxSize = noise(xnoise, ynoise, znoise) * 255;
        float gr = 255 - boxSize;

        float alph = boxSize;
        if (alph > 100) {
          translate(k, j, i);
           if (alph > 150) {
              fill(255, 0);
           } else {
              fill(20, gr + 50, 200, 35);
           }
          box(boxSize, boxSize, boxSize);
        }
        
        popMatrix();
      }
      popMatrix();
    }
    popMatrix();
  }
         translate(150, 0, 0);
         stroke(0,  0);
         noFill();
         box(850, 1800, 1800);
         noStroke();
}