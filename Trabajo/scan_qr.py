import cv2

imagen = cv2.imread("qr.png")

detector = cv2.QRCodeDetector()

datos, matriz, binario = detector.detectAndDecode(imagen)

if matriz is not None:
    print("Datos: " + datos)
