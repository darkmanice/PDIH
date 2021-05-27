setwd("C:/Users/Manolo/Desktop/Javier/Universidad/PDIH/Practicas")

#install.packages('tuneR', dep=TRUE)
#install.packages('seewave', dep=TRUE)
#install.packages("seewave")
library(tuneR)
library(seewave)
library(audio)

#Cargamos el audio del perro.
perro <- readWave('./Sonidos/perro.wav')

#Cargamos el audio del gato.
gato  <- readMP3('./Sonidos/gato.mp3')

#Dibujamos la onda de los sonidos:
plot( extractWave(gato, from = 1, to = 393984) )
plot( extractWave(perro, from = 1, to = 159732) )

#Obtenemos la información de cabecera
str(gato)
str(perro)

#Unimos ambos sonidos
union <- pastew(perro, gato, output = "Wave")
plot( extractWave(union, from = 1, to = 553716) )

#Filtramos las frecuencias
filtrado <- bwfilter(union, n=1, from = 10000, to = 20000, bandpass = TRUE, listen = FALSE, output = "Wave")
plot(extractWave(filtrado, from = 1, to = 553716))

#Almacenamos la señal obtenida
writeWave(filtrado, file.path("Sonidos/mezcla.wav"))

#Cargar un nuevo archivo de sonido, aplicarle eco y a continuación
#darle la vuelta al sonido. Almacenar la señal obtenida como un fichero WAV
#denominado "alreves.wav"
hola <- readWave('./Sonidos/hola.wav')
listen(hola, hola@samp.rate)
alreves <- echo(hola, hola@samp.rate, amp=c(0.8, 0.4, 0.2), delay=c(1, 2, 3), output = "Wave")
alreves <- revw(alreves, f=alreves@samp.rate, output = "Wave")
listen(alreves, alreves@samp.rate)
writeWave(alreves, file.path("./Sonidos/alreves.wav"))
