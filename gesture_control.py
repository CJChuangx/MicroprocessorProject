import cv2
import mediapipe as mp
import keyboard
import math
import time

time.sleep(2)
cap = cv2.VideoCapture(0)
mpHands = mp.solutions.hands
mpDraw = mp.solutions.drawing_utils
mpDraw_styles = mp.solutions.drawing_styles


with mpHands.Hands(
        model_complexity=0,
        min_detection_confidence=0.5,
        min_tracking_confidence=0.5) as hands:
    while True:
        success, img = cap.read()
        imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        results = hands.process(imgRGB)
        lmList = []

        if results.multi_hand_landmarks:
            for handLms in results.multi_hand_landmarks:
                myHand = results.multi_hand_landmarks[0]
                for id, lm in enumerate(myHand.landmark):
                    h, w, c, = img.shape
                    cx, cy = int(lm.x * w), int(lm.y * h)
                    lmList.append([id, cx, cy])

        if len(lmList) != 0:
            x1, y1 = lmList[4][1], lmList[4][2]
            x2, y2 = lmList[8][1], lmList[8][2]

            cv2.circle(img, (x1, y1), 5, (255, 0, 0), cv2.FILLED)
            cv2.circle(img, (x2, y2), 5, (255, 0, 0), cv2.FILLED)

            length = math.hypot(x2 - x1, y2 - y1)

            if (length >= 0) and (length <= 50):
                cv2.line(img, (x1, y1), (x2, y2), (0, 0, 255), 3)
                keyboard.press_and_release('1')
            elif (length >= 51) and (length <= 100):
                cv2.line(img, (x1, y1), (x2, y2), (0, 255, 0), 3)
                keyboard.press_and_release('2')
            elif (length >= 101) and (length <= 150):
                cv2.line(img, (x1, y1), (x2, y2), (100, 100, 100), 3)
                keyboard.press_and_release('3')
            elif length >= 151:
                cv2.line(img, (x1, y1), (x2, y2), (255, 0, 0), 3)
                keyboard.press_and_release('4')


        cv2.imshow("Image", img)
        cv2.waitKey(1)

