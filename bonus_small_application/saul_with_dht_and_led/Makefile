# name of your application
APPLICATION = saul_with_dht_led

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

# we want to use SAUL:
USEMODULE += saul
USEMODULE += dht
USEMODULE += saul_default
USEMODULE += ztimer_usec
USEMODULE += ztimer_sec


#we need this flags to define the pin number and parameter from dht_params.h
CFLAGS += "-DDHT_PARAM_PIN=(GPIO_PIN(0,3))"
CFLAGS += "-DDHT_PARAM_PULL=(GPIO_IN_PU)"


# include the shell:
USEMODULE += shell_cmds_default
# additional modules for debugging:
USEMODULE += ps

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
