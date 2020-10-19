default:
	$(MAKE) --no-print-directory install-all

# Build Program
build:
	gcc headset.c -o dist/headset
	sudo chmod +x dist/*.sh
	
# Install Dependencies works only on Ubuntu (apt supported distros)
install-dep:
	sudo apt install ofono
	sudo apt install ofono-phonesim

# Move files to directories
install:
	$(MAKE) --no-print-directory build
	sudo git clone git://git.kernel.org/pub/scm/network/ofono/ofono.git /bin/ofono
	sudo cp dist/*.sh dist/*.conf dist/headset /bin/
	sudo chmod +x /bin/*.sh

# Install All
install-all:
	$(MAKE) --no-print-directory install-dep
	$(MAKE) --no-print-directory install

# Reinstall program
reinstall:
	sudo rm -r /bin/a2dp.sh /bin/connect.sh /bin/handsfree.sh
	$(MAKE) --no-print-directory build
	sudo cp dist/*.sh dist/*.conf dist/headset /bin/
	sudo chmod +x /bin/*.sh

# Uninstall Program
uninstall:
	sudo rm -r /bin/a2dp.sh /bin/connect.sh /bin/handsfree.sh /bin/ofono

# Uninstall Dependencies
uninstall-dep:
	sudo apt remove ofono
	sudo apt remove ofono-phonesim

# Uninstall All
uninstall-all:
	$(MAKE) --no-print-directory uninstall-dep
	$(MAKE) --no-print-directory uninstall