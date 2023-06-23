# name of your application
APPLICATION = saul_temperature_with_led

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# we want to use SAUL:
USEMODULE += saul_default
# include the shell:
USEMODULE += shell_cmds_default
# additional modules for debugging:
USEMODULE += ps

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

# Use a peripheral timer for the delay, if available
FEATURES_OPTIONAL += periph_timer

include $(RIOTBASE)/Makefile.include
