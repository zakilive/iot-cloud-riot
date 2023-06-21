#include <stdio.h>
#include "dht.h"
#include "saul_reg.h"
#include "saul.h"


static void _dht_func(void) {
	static saul_reg_t *saul_dht;
	static phydat_t result;
	saul_dht = saul_reg_find_name("dht");

	int res = saul_reg_read(saul_dht, &result);

	if(res) {
		printf("temperature: %d %d", result.val[0], result.val[1]);
	} else {
		printf("Sensor read failure: %d\n", res);
	}
}

int main(void)
{

	_dht_func();

	return 0;
}
