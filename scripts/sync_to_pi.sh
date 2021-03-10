# docker exec opendms /bin/bash -c 'cp /install_aarch64/lib /home/lyy/code/opendms/build/lib -rv'
# scp -rv ../build/install_aarch64/lib firefly@192.168.50.38:/home/firefly/test/ 
scp -v ../build/demo firefly@192.168.50.38:/home/firefly/test/bin/
# scp -v ../cfg.json firefly@192.168.50.38:/home/firefly/test/
# scp -rv ../models/ firefly@192.168.50.38:/home/firefly/test/