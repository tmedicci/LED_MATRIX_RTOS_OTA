// System

#include "espressif/esp_common.h"
#include "espressif/esp_system.h"

#include <espconn.h>


// Project
#include "mxp.h"

typedef void (*led_callback)(uint8_t buffer[][3], uint16_t pixels, uint16_t offset);
led_callback callback;

void onMxpRecv(void *arg, char *dat, uint16_t len) {
	uint16_t length = dat[3] * 0xff + dat[4];
	uint16_t offset = dat[1] * 0xff + dat[2];
	//uart0_tx_buffer(dat,len);

	/*** Copy buffer data into static memory to pass a pointer to callback function ***/
	uint16_t i;
	static uint8_t buf[MXP_MAXLEN][3];
	for (i = 0; i < length * 3; ++i)
		buf[i / 3][i % 3] = dat[5 + i];

	callback(buf, length, offset);
}

void mxp_init(led_callback led_cb) {
	callback = led_cb;
	static struct espconn mxpserv;

	mxpserv.type = ESPCONN_UDP;
	mxpserv.proto.udp = (esp_udp *)os_zalloc(sizeof(esp_udp));
	mxpserv.proto.udp->local_port = MXP_UDP_PORT;
	espconn_regist_recvcb(&mxpserv, onMxpRecv);
	espconn_create(&mxpserv);
}
