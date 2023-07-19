#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <irq.h>
#include <uart.h>
#include <console.h>
#include <generated/csr.h>

#include "delay.h"

static char *readstr(void)
{
	char c[2];
	static char s[64];
	static int ptr = 0;

	if(readchar_nonblock()) {
		c[0] = readchar();
		c[1] = 0;
		switch(c[0]) {
			case 0x7f:
			case 0x08:
				if(ptr > 0) {
					ptr--;
					putsnonl("\x08 \x08");
				}
				break;
			case 0x07:
				break;
			case '\r':
			case '\n':
				s[ptr] = 0x00;
				putsnonl("\n");
				ptr = 0;
				return s;
			default:
				if(ptr >= (sizeof(s) - 1))
					break;
				putsnonl(c);
				s[ptr] = c[0];
				ptr++;
				break;
		}
	}
	return NULL;
}

static char *get_token(char **str)
{
	char *c, *d;

	c = (char *)strchr(*str, ' ');
	if(c == NULL) {
		d = *str;
		*str = *str+strlen(*str);
		return d;
	}
	*c = 0;
	d = *str;
	*str = c+1;
	return d;
}

static void prompt(void)
{
	printf("RUNTIME>");
}

static void help(void)
{
	puts("Available commands:");
	puts("help                            - this command");
	puts("reboot                          - reboot CPU");
	puts("led                             - led test");
	puts("switch                          - switch test");
	puts("display                         - display test");
	puts("rgbled                          - rgb led test");
	puts("servo                     	- servomotor test");
	puts("ultra                    	- ultrasonido test");
	puts("radar                           - Radar_test");
	puts("parla                           - parlante_test");
	puts("maestro                         - Inicio Programa");
}

static void reboot(void)
{
	ctrl_reset_write(1);
}

static void display_test(void)
{
	int i;
	printf("display_test...\n");
	for(i=0; i<6; i++) {
		display_sel_write(i);
		display_value_write(7);
		display_write_write(1);
	}
}

static void led_test(void)
{
	unsigned int i;
	printf("Test del los leds... se interrumpe con el botton 1\n");
	while(!(buttons_D_in_read()&1)) {

	for(i=1; i<65536; i=i*2) {
		leds_out_write(i);
		delay_ms(50);
	}
	for(i=32768;i>1; i=i/2) {
		leds_out_write(i);
		delay_ms(50);
	}
	}
	
}

static void switch_test(void)
{
	unsigned short temp2 =0;
	printf("Test del los interruptores... se interrumpe con el botton 1\n");
	while(!(buttons_D_in_read()&1)) {
		unsigned short temp = switchs_in_read();
		if (temp2 != temp){
			printf("switch bus : %i\n", temp);
			leds_out_write(temp);
			temp2 = temp;
		}
	}
}

static void rgbled_test(void)
{
	unsigned int T = 128;
	
	ledRGB_1_r_period_write(T);
	ledRGB_1_g_period_write(T);
	ledRGB_1_b_period_write(T);

	ledRGB_1_r_enable_write(1);
	ledRGB_1_g_enable_write(1);
	ledRGB_1_b_enable_write(1);

	
	ledRGB_2_r_period_write(T);
	ledRGB_2_g_period_write(T);
	ledRGB_2_b_period_write(T);
	
	
	ledRGB_2_r_enable_write(1);
	ledRGB_2_g_enable_write(1);
	ledRGB_2_b_enable_write(1);

	for (unsigned int j=0; j<100; j++){
		ledRGB_1_g_width_write(j);
		for (unsigned int i=0; i<100; i++){
			ledRGB_1_r_width_write(100-i);
			ledRGB_1_b_width_write(i);	
			delay_ms(20);
		}	
	}
	
}

/*
static void vga_test(void)
{
	int x,y;
	
	for(y=0; y<480; y++) {
		for(x=0; x<640; x++) {
			vga_cntrl_mem_we_write(0);
			vga_cntrl_mem_adr_write(y*640+x);
			if(x<640/3)	
				vga_cntrl_mem_data_w_write(((int)(x/10)%2^(int)(y/10)%2)*15);
			else if(x<2*640/3) 
				vga_cntrl_mem_data_w_write((((int)(x/10)%2^(int)(y/10)%2)*15)<<4);
			else 
				vga_cntrl_mem_data_w_write((((int)(x/10)%2^(int)(y/10)%2)*15)<<8);
			vga_cntrl_mem_we_write(1);
		}
	}
}
*/

static int medir_distancia1(void)
{
	ultrasonido_cntrl1_init_write(1);
	delay_ms(2);
	while(1){
		if(ultrasonido_cntrl1_done_read() == 1){
			int distancia = ultrasonido_cntrl1_distance_read();
			ultrasonido_cntrl1_init_write(0);
			return distancia;
		}
	}
}

static int medir_distancia2(void)
{
	ultrasonido_cntrl2_init_write(1);
	delay_ms(2);
	while(1){
		if(ultrasonido_cntrl2_done_read() == 1){
			int distancia = ultrasonido_cntrl2_distance_read();
			ultrasonido_cntrl2_init_write(0);
			return distancia;
		}
	}
}

static void ultrasonido_test1(void)
{
	int d = 0;
	printf("Test de Modulo de Ultrasonido. Para activar oprimir botton 2.\n Para interrumpir oprimir el botton 1.\n");
	while(!(buttons_D_in_read()&1)){
			delay_ms(1000);
			d = medir_distancia1();
			printf("Distancia: %d \n", d);
		
	}
}

static void ultrasonido_test2(void)
{
	int d = 0;
	printf("Test de Modulo de Ultrasonido. Para activar oprimir botton 2.\n Para interrumpir oprimir el botton 1.\n");
	while(!(buttons_D_in_read()&1)){
			delay_ms(1000);
			d = medir_distancia2();
			printf("Distancia: %d \n", d);
		
	}
}

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

static void Radar_test(void)
{
	printf("Test de Modulo de Radar.");
	const int Centro = 0;
	const int Izquierda = 1;
	const int Derecha = 2;
	int distance =0;
	servomotor_cntrl1_posicion_write(Centro);
	servomotor_cntrl2_posicion_write(Centro);
	delay_ms(1000);
	distance = medir_distancia1();
	printf("\nDistancia: %d",distance);
	delay_ms(100);

	servomotor_cntrl1_posicion_write(Izquierda);
	servomotor_cntrl2_posicion_write(Izquierda);
	delay_ms(1000);
	distance = medir_distancia1();
	printf("\nDistancia: %d",distance);
	delay_ms(100);

	servomotor_cntrl1_posicion_write(Derecha);
	servomotor_cntrl2_posicion_write(Derecha);
	delay_ms(1000);
	distance = medir_distancia1();
	printf("\nDistancia: %d",distance);
	delay_ms(100);

	servomotor_cntrl1_posicion_write(3);
	servomotor_cntrl2_posicion_write(3);
}

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
 	// else if ((distance>350 && distance <=450)){
 	// 	while(ban<=2){
	// 		parlante_cntrl_enable_write(1);
	// 		parlante_cntrl_max_cont_write(lejos);
	// 		delay_ms(100);
	// 		parlante_cntrl_enable_write(0);
	// 		delay_ms(100);
	// 		ban= ban +1;
	// 	}
 	// }
	
 } 

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
		//servomotor_cntrl2_posicion_write(Centro)
		//delay_ms(1000);
		distance = medir_distancia2();
		printf("\n distancia: %d",distance);
		parlante(distance);
		delay_ms(80);
	}
}

static void console_service(void)
{
	char *str;
	char *token;

	str = readstr();
	if(str == NULL) return;
	token = get_token(&str);
	if(strcmp(token, "help") == 0)
		help();
	else if(strcmp(token, "reboot") == 0)
		reboot();
	else if(strcmp(token, "led") == 0)
		led_test();
	else if(strcmp(token, "switch") == 0)
		switch_test();
	else if(strcmp(token, "display") == 0)
		display_test();
	else if(strcmp(token, "rgbled") == 0)
		rgbled_test();
/*	else if(strcmp(token, "vga") == 0)
		vga_test();
*/	
	else if(strcmp(token, "servo") == 0)
		servomotor_test();
	else if(strcmp(token, "ultra1") == 0)
		ultrasonido_test1();
	else if(strcmp(token, "ultra2") == 0)
		ultrasonido_test2(); 
	
	else  if(strcmp(token, "parla") == 0)
		parlante(251);
	// 	/* delay_ms(1000);
	// 	parlante(300);
	// 	delay_ms(1000);
	// 	parlante(370) */
	else  if(strcmp(token, "radar") == 0)
		Radar_test();
	else  if(strcmp(token, "maestro") == 0)
		Maestro();
	prompt();
}

int main(void)
{
	#ifdef CONFIG_CPU_HAS_INTERRUPT
	irq_setmask(0);
	irq_setie(1);
	#endif
	uart_init();

	puts("\nSoC - RiscV project UNAL 2022-2"__DATE__" "__TIME__"\n");
	help();
	prompt();
	Maestro();
	// int tine=0.0001;
	// PWM_enable_write(1);
	// PWM_period_write(tine);
	// PWM_width_write(tine/2);
	//printf(" \n");
	// while(!(buttons_ul_del_in_read()&1)){//Si se presiona el boton, entra el while
	// 	printf("derecha");
	// 	delay_ms(60);
	// }
	// if((buttons_ul_tra_in_read()&1)){//Siempre imprime
	// 	printf("izquierda");
	// }
	// if((buttons_ul_tra_in_read()&(1<<1))){
	// 	printf("atras");
	// }


	while(1) {
		console_service();
	/*	leds_out_write(15);
		delay_ms(100);
		leds_out_write(240);
		delay_ms(100);
		printf("El programa \n");*/
	}

	return 0;
}
