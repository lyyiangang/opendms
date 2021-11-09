xhost +local:${USER}
docker run -it --rm     \
    -u $(id -u) \
    -e DISPLAY=$DISPLAY     \
    -v ${HOME}/.ssh:/.ssh \
    -v ${HOME}/.ssh:/root/.ssh \
    -v /tmp/.X11-unix:/tmp/.X11-unix     \
    -v ${PWD}:${PWD} \
    -w ${PWD} \
    --name opendms \
    opendms
