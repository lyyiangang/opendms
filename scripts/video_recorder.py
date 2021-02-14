import numpy as np
import cv2
import subprocess

print('device support resultion:')
subprocess.call("v4l2-ctl --list-formats-ext", shell = True)
video_size = (1280, 720) #width and height
begin_record = False
output_file = "../p_data/ir_{}x{}.avi".format(video_size[0],video_size[1])
cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, video_size[0])
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, video_size[1])
fourcc = cv2.VideoWriter_fourcc(*'XVID')

out_video_writer = None
while(cap.isOpened()):
    ret, frame = cap.read()
    if ret==True:
        key =  cv2.waitKey(1) & 0xFF 
        if key == ord('q'):
            break
        elif key == ord('s'):
            begin_record = not begin_record

        if begin_record:
            if not out_video_writer :
                print(f'writing video to {output_file}')
                out_video_writer =  cv2.VideoWriter(output_file, fourcc, 30.0, video_size)
                print(f'frame shape:{frame.shape}')
            out_video_writer.write(frame)
        cv2.putText(frame, "Recording:"+str(begin_record), (0,30),cv2.FONT_HERSHEY_COMPLEX,0.8,(0,0,255))
        cv2.putText(frame, "File name:"+ output_file, (0,60),cv2.FONT_HERSHEY_COMPLEX,0.8,(0,0,255))
        cv2.putText(frame, "press 's' to record video and 'q' to exit.", (0,90),cv2.FONT_HERSHEY_COMPLEX,0.8,(0,0,255))
        
        cv2.imshow('frame',frame)

    else:
        break

cap.release()
out_video_writer.release()
cv2.destroyAllWindows()