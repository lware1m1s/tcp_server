# tcp_server

Purpose of this server is to allow for the following commands
1. INCR [VALUE] - increment counter on server by specified value
2. DECR [VALUE] - decrement counter on server by specified value
3. OUTPUT

# systemd integration
In order to run this server as a systemd process, an apporpiate unit file will have to created. 
The service would have to enabled with systemctl and associated unit would have to be turned on
with journalctl to start message logging.

