# Purdue-globalTeamProject

<u><h2>This project is for CNIT 390 Class in Purdue University from 2021-09-10 to 2021-12-20.</h2></u>

### **Warning !**<u><h3>This paper "[Crack detecting method with YOLOv3.pdf](https://github.com/laykis/Purdue-globalTeamProject/blob/master/Crack%20detecting%20method%20with%20YOLOv3.pdf)" is an unpublished paper. we inform you that it was for recording the experience of writing the paper.</h3></u>
---  
![image](https://user-images.githubusercontent.com/73100987/193774540-c151c292-dc6c-4478-8432-c40b6393051f.png)
![image](https://user-images.githubusercontent.com/73100987/193774572-fe48ef22-865a-4008-b0c2-8fd8e77b05ae.png)

---
### **INTRODUCTION**

This project is about method that how to detect the crack on structure.

##### **Team Member**

- *Wonkwnag Univ*
  - Dohyeon Kim
    - Writing paper
    - Data Labeling
    - Collecting crack image on campus
  - Kang Lee
    - Getting results from the program(Adjusting weights file)
    - Writing paper
  - Sanha Choi
    - Writing paper
    - Data Labeling
  
- *Purdue Univ*
  - Christian Elfreich
    - Analyze algorithm
  - Kichang Kang
    - Writing Paper
    - Collecting crack image on campus
  - Evan McClain
    - Make RaspBerry pi stuff
    - Writing paper
  - Wes Johnston
    - Collecting crack image on campus
    - Writing paper
  - Brandon Lee
    - Collecting crack image on campus
    - Writing paper
  - Scott Stevens
    - Collecting crack image on campus
    - Writing paper

---

### **System Overview**

<img width="827" alt="image" src="https://user-images.githubusercontent.com/73100987/193781954-bf9d526e-76e3-4826-8671-e016b68f5013.png">

1. Labeling the images of cracks.

2. Training on Yolo detection model.

3. Mounting the "Yolo crack detection model" on Raspberry PI.

4. You can find the cracks on Structure via Raspberry PI camera.

---

### **Experiment**

##### **First, Second Model**

<img width="637" alt="image" src="https://user-images.githubusercontent.com/73100987/193783604-c5db081e-c11f-4fc0-85d9-f6cec845b9f4.png">

##### **Result**

It detects not only cracks but other objects like walls, concrete, and even humans as a crack. 

It seems that the model trains common and biased characteristics of cracks, so there is a possibility that the model is overfitted. 

A phenomenon in which the model is trained closer to the distribution of training samples than to the actual distribution is overfitting.

##### We have to regularization this model to prevent overfitting.


##### **Third Model**

<img width="563" alt="image" src="https://user-images.githubusercontent.com/73100987/193784283-3b5e39d0-b33a-4397-bf26-d37e3508fae7.png">


##### **Result**

Third model trains 9,000 images of mixed METU datasets which are not on concrete, SDNET and custom datasets which we take a photo on concrete structures, sidewalks.

Its average data loss rate is kept lower and there is no phenomenon that detects other objects as a crack.

---
### **Conclusion**

We suggest put this model(Raspberry PI camera) on Drone.

Drone will provide you convenience for detecting cracks on tall building or dangerous place.

---

### **Certification**

![image](https://user-images.githubusercontent.com/73100987/193785138-b7b44953-20c5-40da-aa3b-044953d31901.png)


