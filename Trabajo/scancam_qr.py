import cv2

cap = cv2.VideoCapture(0)
imagen = cv2.imread("qr.png")

detector = cv2.QRCodeDetector()

while True:
    _, imagen = cap.read()

    datos, matriz, _ = detector.detectAndDecode(imagen)

    if matriz is not None:
        print("Datos: " + datos)

    if cv2.waitKey(0) == ord("q"):
        break
cap.release()
