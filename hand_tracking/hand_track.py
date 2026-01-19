import cv2
import mediapipe as mp
import math
from pythonosc import udp_client

OSC_IP = "127.0.0.1"
OSC_PORT = 3333
CAMERA_INDEX = 0 #issam tu dois ptet changer ça chez toi 
client = udp_client.SimpleUDPClient(OSC_IP, OSC_PORT)

mp_hands = mp.solutions.hands
mp_draw = mp.solutions.drawing_utils


hands = mp_hands.Hands(
    static_image_mode=False,
    max_num_hands=2,
    model_complexity=0,      
    min_detection_confidence=0.5,
    min_tracking_confidence=0.5
)

def get_dist(p1, p2):
    return math.hypot(p2.x - p1.x, p2.y - p1.y)

cap = cv2.VideoCapture(CAMERA_INDEX)


while cap.isOpened():
    success, img = cap.read()
    if not success:
        continue

    img = cv2.flip(img, 1)
    h, w, c = img.shape
    img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    results = hands.process(img_rgb)

    if results.multi_hand_landmarks and results.multi_handedness:
        for hand_lms, hand_info in zip(results.multi_hand_landmarks, results.multi_handedness):
            label = hand_info.classification[0].label
            if label == "Left":
                index_tip = hand_lms.landmark[8]
                cx, cy = int(index_tip.x * w), int(index_tip.y * h)
                cv2.circle(img, (cx, cy), 15, (255, 0, 0), cv2.FILLED)
                osc_x = float(index_tip.x)
                osc_y = float(1.0 - index_tip.y) 
                client.send_message("/attractor/pos", [osc_x, osc_y, 0.0])
            if label == "Right":
                thumb_tip = hand_lms.landmark[4]
                index_tip = hand_lms.landmark[8]
                x1, y1 = int(thumb_tip.x * w), int(thumb_tip.y * h)
                x2, y2 = int(index_tip.x * w), int(index_tip.y * h)
                cv2.line(img, (x1, y1), (x2, y2), (0, 255, 0), 3)
                cv2.circle(img, (x1, y1), 10, (0, 255, 0), cv2.FILLED)
                cv2.circle(img, (x2, y2), 10, (0, 255, 0), cv2.FILLED)
                distance = get_dist(thumb_tip, index_tip)
                
                radius_val = max(10.0, distance * 500.0) #tu peux bouger ça si t'as des ptites mains espèce de neuil 
                
                cv2.putText(img, f"Radius: {int(radius_val)}", (x2+20, y2), 
                            cv2.FONT_HERSHEY_PLAIN, 2, (0, 255, 0), 2)

                client.send_message("/attractor/radius", [float(radius_val)])

            mp_draw.draw_landmarks(img, hand_lms, mp_hands.HAND_CONNECTIONS)

    cv2.imshow("Handtracking", img)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
