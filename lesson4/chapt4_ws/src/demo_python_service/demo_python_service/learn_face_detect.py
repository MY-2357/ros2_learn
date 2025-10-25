import face_recognition
import cv2
import os
from ament_index_python import get_package_share_directory

def main():
    default_image_path=os.path.join(get_package_share_directory('demo_python_service'),'resource/default.jpg')
    print(default_image_path)
    image=cv2.imread(default_image_path)
    face_locations=face_recognition.face_location(image,model='hog')
    for top,right,bottom,left in face_locations:
        cv2.rectangle(image,(left,top),(right,bottom),(255,0.0),4)
        cv2.imshow('Face Detect Result',image)
        cv2.waitKey(0)
