struct message{
	long type;
	char body[12];
	};
typedef struct message tMessage;

#define SIZE_MSG sizeof(tMessage) - sizeof(long)
#define PATH "SharedPumper.h"
#define TYPE_1 1L // mensaje a vip
#define TYPE_2 2L  // mensaje a normal
#define TYPE_3 3L // mensaje de derivar pedido a hamburguesa
#define TYPE_4 4L //mensaje de derivar pedido a vegano
#define TYPE_5 5L //mensaje de derivar pedido a papas

#define TYPE_6 6L // mensaje hamburguesa al cliente que pidio
#define TYPE_7 7L // mensaje vegano al cliente que pidio
#define TYPE_8 8L // mensaje papas al cliente que pidio
