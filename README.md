# Proyecto: SISTEMA DE GUÍA PARA PERSONA CON VISIÓN REDUCIDA
	
## Resumen

En este documento se presenta el planteamiento, diseño e implementación de un sistema de alerta de proximidad para que usuarios con visión reducida puedan evitar colisionarse con obstáculo. Asimismo, mediante la ejecución de software, hardware y la construcción de un prototipo, evidenciar como la tecnología ayuda a solucionar problemas y mejorar la calidad de vida de las personas.

## Introducción 

En la actualidad, las personas invidentes no cuentan con herramientas completas para recibir un servicio de apoyo lo suficientemente práctico durante sus desplazamientos en las calles, situación que genera mayores niveles de riesgo a su integridad física. En Colombia se tiene que alrededor del 7.2\% de la población presenta bajos niveles de visión; se han intentado implementar soluciones como el Bastón Blanco, Braille, el perro guía, entre otras; sin embargo, la tecnología presenta muchos desarrollos que hasta el momento aún siguen siendo aplicados para esta problemática. Sacando provecho de estos nuevos dispositivos, se pueden idear soluciones más efectivas, capaces de facilitar sus procesos de movilización, mientras se ve enriquecida su calidad de vida. Es necesario emplear la electrónica y la tecnología para aportar a las personas con capacidades reducidas, mejorando así los niveles de inclusión y equidad en el país. 

## Objetivos 

### General

Diseñar y crear un dispositivo capaz de aletar a las personas con visión reducida cuando se encuentre a determinadas distancias de un obstáculo, facilitando sus procesos de movilización mientras se disminuyen los niveles de riesgo a los que se exponen. Aplicando para esto los conocimientos adquiridos a lo largo del semestre en la asignatura de Electrónica Digital II y en los procesos de investigación desarrollados en el presente proyecto.

### Específicos

- Diseñar un sistema de sensores capaz de reconocer obstáculos físicos a determinada distancia, que puedan presentar un riesgo de colisión para el usuario.
- Aplicar el diseño a un montaje en la tarjeta FPGA con periféricos externos adicionales, un parlante de alerta y tres botones de cambio de dirección.
- Implementar el sistema diseñado en un prototipo para uso práctico del usuario; para este caso, una maleta/mochila convencional.
- Profundizar y aplicar los conocimientos adquiridos en la asignatura Electrónica Digital II. 


## Justificación

La importancia del proyecto está en evidenciar cómo los desarrollos tecnológicos se involucran para solucionar problemas y mejorar la calidad de vida de las personas. Además, aplicar de forma práctica e innovadora los conocimientos adquiridos a través del curso de Electrónica Digital II y mejorar las habilidades de investigación de los y las integrantes del grupo de trabajo.

## Evolución

Inicialmente el proyecto nace como herramienta para personas con discapacidad visual, por lo tanto se plantea el uso de sensores de proximidad capaces de alertar mediante motores vibratorios de la presencia de objetos cercanos al usuario, sin embargo, a medida que se avanza en el proyecto decidimos modificar dichos motores por una bocina cuyo sonido sea el aviso dado, el sonido producido se controla mediante un divisor de frecuencia desde Hardware, lo cuál nos permite tener la opción de modificar dicha frecuencia a medida que se detecta una mayor cercanía por parte del objeto.

Más adelante, definimos el montaje del proyecto, en dónde el acuerdo fue que una maleta adaptada sería la mejor herramienta para llevar a cabo el mismo, por tan razón decidimos adaptar el sistema de esa forma, logrando que el usuario pueda transportar cómodamente el dispositivo, mientras esta protegido de daños por posibles perturbaciones. 

Por último se adapto un banco de batería y unos servomotores a fin de lograr un dispositivo completamente funcional; la primera para que sea posible transportarlo y usarlo en diferentes escenarios, la segunda para lograr un mayor rango y que los sensores ultrasónicos puedan girarse a fin de revisar los diferentes ángulos y movimientos del usuario. Así mismo, se adaptaron botones para permitir habilitar los movimientos de los servomotores.

## Alcance y Proyección 

Se pretende presentar en esta primera etapa hasta obtener una maleta capaz de detectar objetos a un máximo de 3,5m de distancia, manejando dos frecuencias en la alarma dónde la más intensa se activaría a 60 cm; el prototipo presenta tres botones, dos en el lado izquierdo para este lado y la parte de atrás, otro botón en el lado derecho para llegar a esta dirección. Así mismo se tiene un parlante en la parte trasera para el funcionamiento de la alarma, la tarjeta se encuentra al interior de la maleta y en la parte superior de las correas están los servomotores y los sensores. 

A futuro se proyectan mejoras reflejadas en una modificación para poder conectarse al celular, de tal forma que sea posible de emplear mediante auriculares; además se piensa en más variaciones de frecuencia para la alarma de tal forma que sean claros los rangos de distancia que se tienen entre los objetos y los usuarios; también se podría probar en otros wearables. Por último, se espera añadir diferentes modos de uso, teniendo en cuento que se pueden presentar varios escenarios como transporte público, interiores, la calle, entre otros y para cada uno las condiciones son diferentes.

## [ Mapa de Memoria ](/SoC_project/csr.csv)
En la presente sección se encuentran los diferentes perífericos que se usaron para la elaboración del SISTEMA DE GUÍA PARA PERSONA CON VISIÓN REDUCIDA.

## Perifericos 

Los periféricos utilizados para la elaboración de este sistema de guía son:

- #### Servomotor:
El driver de este periférico se encuentra basado en una señal PWM, la cual es generada mediante hardware. Este cuenta con 3 direcciones a las cuales puede moverse dependiendo de la duración de la señal PWM. El codigo utilizado para la descripcion de este periferico es:
```verilog
`timescale 1ns / 1ps
module servomotor(  input clk, // Reloj

                    // Registros
                    input [1:0] posicion,

                    // Conexiones del Dispositivo
                    output reg servo 
                    );

// Registros auxiliares
reg [20:0] contador = 0;

always@(posedge clk)begin
	contador = contador + 1;
	if(contador == 'd1_000_000) begin
	    contador = 0;
	end
	
	case(posicion)
        // Centro
        2'b00:  servo = (contador < 'd150_000) ? 1:0;
        // Izquierda
        2'b01:  servo = (contador < 'd250_000) ? 1:0;
        // Derecha
        2'b10:  servo = (contador < 'd50_000) ? 1:0;
        // Caso por Defecto (Centro)
        default:servo = (contador < 'd150_000) ? 1:0;
    endcase
end

endmodule

```

- #### Sensor Ultrasónico:
El driver de este periférico se basa en una maquina de estados que cuenta con 3 estados, los cuales son start, pulse y echo. A continuacion se ve el codigo verilog.
```verilog
`timescale 1ns / 1ps
module ultrasonido( input clk, // Reloj

                    // Registros
                    input init,
                    output reg [8:0] distance,
                    output reg done,

                    // Conexiones del Dispositivo
                    input echo,
                    output reg trig
                    );

wire clk_1MHz; // Reloj de 1MHz

// Registros auxiliares
reg [14:0] counter = 0;
reg echoStart = 0;

reg [1:0] status = 0; // Registro de Estado
parameter Start = 0, Pulse = 'd1, Echo = 'd2; // Estados

always @ (posedge clk_1MHz) begin
    case(status)
        Start:  begin
                    // Cuando init es 1, se reinician los registros.
                    if(init) begin
                        done = 0;
                        counter = 0;
                        distance = 0;
                        status = Pulse;
                    end
                end
        Pulse:  begin
                    // Trig cambia a 1 por 11 us, luego regresa 0.
                    trig = 1'b1;
                    counter = counter + 1'b1;
                    if(counter == 'd11) begin
                        trig = 0;
                        counter = 0;
                        status = Echo;
                    end
                end
        Echo:   begin
                    // Se espera a que echo sea 1, luego se contabiliza el tiempo hasta que echo sea 0.
                    if(echo) begin
                        echoStart = 1;
                        counter = counter + 1'b1;
                    end
                    if(echo == 0 && echoStart == 1) begin
                        // Si el contador es 0, se vuelve al estado anterior hasta que el resultado sea diferente a 0.
                        if(counter == 0) status = Pulse;
                        else begin
                            // Se divide el contador entre 58 para encontrar la distancia
                            distance = counter/'d58;
                            status = Start;
                            done = 1;
                        end
                    end
                end
    endcase 
end

endmodule

```

En el estado start, se reinician todos los registros y se pasa al estado estado pulse, donde se manda una se manda una señal por el puerto trigger del periférico, luego se pasa al estado echo, donde se toma el tiempo, que transcurren entre la salida y el regreso de la señal enviada en el estado trigger, luego de esto, este tiempo, se divide entre 58 para asi obtener la distancia, todo este proceso es realizado mediante hardware.

- #### Parlante:
El parlante se basa en un divisor de frecuencia, con el cual se busca obtener frecuencias que se encuentren dentro del rango auditivo de los seres humanos pues este actuara como alarma de proximidad para la persona con visión reducida.
```verilog
`timescale 1ns / 1ps
module parlante(	input clk, // Reloj de Entrada
				input [28:0] max_cont, // Valor maximo para contador dado por [max_cont = 100Mhz/(2*Frecuencia Nueva)]
				output reg freq,
				input  enable // Reloj de Salida 
				);

initial begin
    freq= 0;
end

// Registros auxiliares
reg [28:0] contador = 0;

always @(posedge clk) begin
	//Cuenta hasta el valor de max_cont
	contador = contador + 1'b1;
	if(contador == max_cont) begin
		//Se reinicia el contador y se niega el valor de newCLK
		contador = 0;
		if (enable)
			freq = !freq;
		else begin
			freq =0;
		end
	end
end

endmodule

```

- #### Botones: Se implementaron tres pulsadores normalmente abiertos conectados a la alimentación, que mediante software, envían la instrucción a los servomotores de cambiar la dirección de medición de los sensores ultrasónicos, la cual es siempre hacia al frente.


Cabe destacar que tanto el servomotor como el parlante, son controlados mediante software, pues se puede cambiar la dirección del servo y la frecuencia a la que suena la bocina. En el caso del ultrasónico, solo se habilita la funcionamiento y se lee la distancia que fue captada.

## Firmware
A continuacion se muestran las funciones mas importantes para el desarrollo del proyecto, las cuales son utilizadas para las pruebas de los perifericos.

### Funciones Prueba de perifericos

- #### Medir distancia
La función "medir_distancia" es la encargada de al momento de ser llamada realizar una escritura en el registro de inicio del módulo de ultrasonido por lo que este provee una respuesta la cual es impresa.

```C
static int medir_distancia(void)
{
	ultrasonido_cntrl_init_write(1);
	delay_ms(2);
	while(1){
		if(ultrasonido_cntrl_done_read() == 1){
			int distancia = ultrasonido_cntrl_distance_read();
			ultrasonido_cntrl_init_write(0);
			return distancia;
		}
	}
}
```

- #### Servomotor
La función "servomotor_test" es la encargada de al momento de ser llamada realizar una escritura en el registro de posicion del modulo servomotor, por lo cual hace girar el periferico:
```C
static void servomotor_test(void)
{
	const int Centro = 0;
	const int Izquierda = 1;
	const int Derecha = 2;
	printf("Test de Modulo de Servomotor.");
	servomotor_cntrl1_posicion_write(Centro);
	delay_ms(1000);
	servomotor_cntrl2_posicion_write(Centro);
	delay_ms(1000);
	servomotor_cntrl1_posicion_write(Izquierda);
	delay_ms(1000);
	servomotor_cntrl2_posicion_write(Izquierda);
	delay_ms(1000);
	servomotor_cntrl1_posicion_write(Derecha);
	delay_ms(1000);
	servomotor_cntrl2_posicion_write(Derecha);
	delay_ms(1000);
	servomotor_cntrl1_posicion_write(3);
	servomotor_cntrl2_posicion_write(3);

}
```
- #### Parlante
La función "parlante" es la encargada de al momento de ser llamada realizar una escritura en el registro de inicio del módulo de parlante por lo que este dependiendo de la distancia, manda una señal a una frecuencia especifica la cual sera escuchada por medio de un parlante.
```C
static void parlante (int distance)
{
	//const int lejos = 200000;
	const int medio = 100000;
	const int cerca = 66667;
	int ban = 0;
	
 	if (distance>= 2 && distance <=60){
 		while(ban<=2){
			parlante_cntrl_enable_write(1);
			parlante_cntrl_max_cont_write(cerca);
			delay_ms(100);
			parlante_cntrl_enable_write(0);
			delay_ms(100);
			ban= ban +1;
		}
 	}
 	else if ((distance>80 && distance <=350)){
		while(ban<=2){
			parlante_cntrl_enable_write(1);
			parlante_cntrl_max_cont_write(medio);
			delay_ms(300);
			parlante_cntrl_enable_write(0);
			delay_ms(300);
			ban= ban +1;
		}

 	}
 } 
```

### Funcion de integracion 
La funcion "Maestro" es la encargada de la integracion de todos los perifericos en pro de la funcionalidad requerida en este sistema de guia.

```C
static void Maestro(void)
{
	const int Centro = 0;
	const int Izquierda = 1;
	const int Derecha = 2;
	int distance = 0;

	while (!(buttons_D_in_read()&1)){

		if (!(buttons_ul_del_in_read()&(1))){
			servomotor_cntrl1_posicion_write(Izquierda);
			while(!(buttons_ul_del_in_read()&(1))){
				printf("\n Medicion a la izquierda");
				//delay_ms(1000);
				distance = medir_distancia2();
				printf("\n distancia: %d",distance);
				parlante(distance);
				delay_ms(100);
			}
			
		}

		else if(!(buttons_ul_tra_in_read()&(1))){
			servomotor_cntrl2_posicion_write(Izquierda);
			while (!(buttons_ul_tra_in_read()&(1)))
			{
				printf("\n Medicion a la izquierda");
				//delay_ms(1000);
				distance = medir_distancia1();
				printf("\n distancia: %d",distance);
				parlante(distance);
				delay_ms(100);
			}
			
		}

		else if(!(buttons_ul_tra_in_read()&(1<<1))){
			servomotor_cntrl2_posicion_write(Centro);
			while(!(buttons_ul_tra_in_read()&(1<<1))){
				printf("\n Medicion atras");
				//delay_ms(1000);
				distance = medir_distancia1();
				printf("\n distancia: %d",distance);
				parlante(distance);
				delay_ms(100);
			}
		}
		printf("\n Medicion frente");
		servomotor_cntrl1_posicion_write(Centro);
		distance = medir_distancia2();
		printf("\n distancia: %d",distance);
		parlante(distance);
		delay_ms(80);
	}
}
```

## Montaje

Para el montaje del proyecto, se implementó una maleta a la que se adhirieron los servomotores con los sensores en la parte más alta de las correas; para que quedaran al nivel de los hombros del usuario. Se pegaron los tres botones en la zona inferior de las correas, en la correa izuierda un botón de dirección izquierda y cambio de medición hacia atrás, y en la correa derecha el ecargado de cambiar la dirección a la derecha. Se le incrustaron los cables dentro de las correas y se enviaron a través de ellas al interior de la maleta, para que no incomodaran o se enredaran con el usuario. Además se dejó el parlante expuesto en la parte posterior de la maleta, aunque dejando las conexiones de este también en el interior.

Finalmente, se realizó toda la conexión con la FPGA dentro del bolsillo principal de la maleta, y se adecuó la alimentación del prototipo con una batería portatil para mejorar su portabilidad.

# Dificultades Presentadas

En cuanto a las dificultades presentadas, se encuentra, el diseño del periférico para el sensor ultrasónico, pues al estar basado en una maquina de estado, la lógica empieza a ser secuencial por lo cual hace un poco mas complejo el proceso de análisis de esta, adicionalmente también toco incluir un divisor de frecuencia al driver pues, la duración de la señal enviada debe ser de al menos 10uS, para lograr este tiempo, se necesitaba un clock de 1MHz, pero, la fpga utilizada en este proyecto, cuenta con un clock de 100MHz y al relacionar el bloque del periférico con el del divisor de frecuencia se generaron ciertos errores que retuvieron un poco el avance del proyecto.

Por otro, se tiene el parlante, pues al estar basado en un divisor de frecuencia que toma como frecuencia principal el clock de la fpga por lo cual cuando era solicitado por software este no permitía el cambio de una frecuencia de sonido a otra. Este problema se pudo solucionar agregando en hardware un init, el cual habilitaba el funcionamiento del parlante siempre y cuando se necesitara y de la forma en la que se necesitara.

# Conclusiones
 Se logró implementar un procesador en la FPGA, capaz de controlar los periféricos propuestos (parlante, sensores ultrasónicos y servomotores), a fin de cumplir con las funciones establecidas para cada uno.
 
- EL dispositivo fue capaz de reconocer objetos a distancias de 3,5 m o menos, así como lograr variaciones en la frecuencia de alarma para lograr una mayor claridad sobre el obstáculo presente.

- Se logran aplicar los conocimientos sobre estructura de procesadores, unidad de control y datapath, así como, la comunicación entre los mismos; apprendidos a lo largo del curso de Electrónica Digital II.

- Se desarrollaron habilidades y manejo del lenguaje Verilog, así como del diseño desde hardware y software, empleando Litex y Vivado.
