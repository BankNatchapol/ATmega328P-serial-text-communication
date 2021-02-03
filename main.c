#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>

void USART_Init(unsigned int ubrr) {
    /* Set baud rate */
    UBRR0 = ubrr;
    /* Double Transmission Speed*/
    UCSR0A |= (1 << U2X0);
    /* Enable receiver and transmitter */
    UCSR0B |= (1 << RXEN0)|(1 << TXEN0);
    /* Set frame format: 8data */
    UCSR0C |= (1 << UCSZ01)|(1 << UCSZ00);
}

void USART_Transmit( unsigned char data ) {
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1 << UDRE0)) ) ;
    /* Put data into buffer, sends the data */
    UDR0 = data;
}
unsigned char USART_Receive() {
    /* Wait for data to be received */
    while ( !(UCSR0A & (1 << RXC0)) ) ;
    /* Get and return received data from buffer */
    return UDR0;
}

int main(void) {

    int i = 0;
    unsigned char greet[] = "Hello ";
    unsigned char received_char[20];
    
    USART_Init(103);
    
    while (1) {
        
        
        i = 0;
        do
        {
          received_char[i] = USART_Receive();
          i++;
        }
        while(!(received_char[i-1]=='\n'));
        
        i = 0;
        while(greet[i]!=0){
            USART_Transmit(greet[i]);
            i++;
        }
        
        i = 0;
        while(received_char[i]!=0){
            USART_Transmit(received_char[i]);
            i++;
        }
        
        received_char[20]="";
    }
}
