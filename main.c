////zad2////

#include <avr/io.h>
#define F_CPU 16000000L
#include <util/delay.h>

char tab[10]={0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b011111111, 0b01101111}; //deklaracja tablicy zawieraj¹cej cyfry od 0 do 9 do wyswietlenia na wyswietlaczu 7-segmentowym
int i=0;
int j=0;
int k=0;
int l=0;

int s=0;

int c;

void check(){
	if((l*10 + k) > 24){
		l=0;
		k=0;
	}
	
	if(k>9){
		l++;
		k=0;
	}
	
	if((j*10 + i) >= 60){
		j=0;
		i=0;
	}

	if(i>9){
		j++;
		i=0;
	}
}

int main(void)
{
	DDRA = 0b00000111;

	PORTB=0b11111111;
	DDRB=0b11111111;
	DDRD=0b00011111;
	PORTD=0b00010000;

	while (1)
	{
		if(!(PINA & (1<<0))){
			i++;
			for(c=0;c<=15000;c++){
				PORTB=tab[l];
				PORTD=0b00010001;
				_delay_ms(1);
				
				PORTB=tab[k];
				PORTD=0b00010010;
				_delay_ms(1);
				
				PORTB=tab[j];
				PORTD=0b00010100;
				_delay_ms(1);
				
				PORTB=tab[i];
				PORTD=0b00011000;
				_delay_ms(1);
				PORTD=0b00010000;
				
				if(PINA & (1<<0)){
					break;
				}
			}
			if(l>=2 && k==3 && j==5 && i==9){
				l=0;
				k=0;
				j=0;
				i=-1;
			}
			
			if(k>=9 && j==5 && i==9){
				l++;
				k=0;
				j=0;
				i=-1;
			}
			
			if(j>=5 && i>=9){
				k++;
				j=0;
				i=-1;
			}

			if(i>=9){
				j++;
				i=-1;
			}
		}
		else{
			PORTD=0b00000000;
			if(PINA & (1<<1)){
				k++;
				s=1;
				check();
			}
			if(PINA & (1<<2)){
				i++;
				s=1;
				check();
			}
			if(s==1){
				for(c=0;c<=25;c++){
					PORTB=tab[l];
					PORTD=0b00010001;
					_delay_ms(1);
					
					PORTB=tab[k];
					PORTD=0b00010010;
					_delay_ms(1);
					
					PORTB=tab[j];
					PORTD=0b00010100;
					_delay_ms(1);
					
					PORTB=tab[i];
					PORTD=0b00011000;
					_delay_ms(1);
					PORTD=0b00010000;
					
					s=0;
				}
			}
			if(!(PINA & (1<<0))){
				i--;
			}
		}
	}
}
