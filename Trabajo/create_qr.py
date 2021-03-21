import qrcode

datos = "https://www.google.com"
archivo = "qr.png"

qr = qrcode.QRCode(version=2, box_size=15, border=5)
qr.add_data(datos)
qr.make()

imagen = qr.make_image(fill_color="white", back_color="blue")

imagen.save(archivo)
