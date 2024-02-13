from pysnmp.hlapi import *

# Definir los parámetros de autenticación SNMPv3
username = 'tu_usuario'  # Nombre de usuario SNMPv3
auth_password = 'tu_password'  # Contraseña de autenticación SNMPv3
priv_password = 'tu_password_privada'  # Contraseña de encriptación SNMPv3
auth_protocol = usmHMACSHAAuthProtocol  # Protocolo de autenticación SNMPv3 (por ejemplo, SHA)
priv_protocol = usmAesCfb128Protocol  # Protocolo de encriptación SNMPv3 (por ejemplo, AES)

# Definir la dirección IP de cada router
routers = [
    '192.168.1.1',
    '192.168.1.2',
    # Agregar más direcciones IP de routers según sea necesario
]

# Definir el nuevo nombre para cada router
router_names = {
    '192.168.1.1': 'Router1',
    '192.168.1.2': 'Router2',
    # Agregar más direcciones IP y nombres de routers según sea necesario
}

# Recorrer cada router y cambiar el nombre
for router_ip in routers:
    try:
        # Crear un contexto SNMPv3 con los parámetros de autenticación
        snmp_context = SnmpEngine()
        usm_user = UsmUserData(
            username=username,
            authKey=auth_password,
            privKey=priv_password,
            authProtocol=auth_protocol,
            privProtocol=priv_protocol
        )

        # Realizar una solicitud SNMP versión 3 para cambiar el nombre del router
        error_indication, error_status, error_index, var_binds = next(
            setCmd(snmp_context,
                   usm_user,
                   UdpTransportTarget((router_ip, 161)),
                   ContextData(),
                   ObjectType(ObjectIdentity('SNMPv2-MIB', 'sysName', 0), OctetString(router_names[router_ip]))
                   )
        )

        if error_indication:
            print(f"Error en {router_ip}: {error_indication}")
        elif error_status:
            print(f"Error en {router_ip}: {error_status.prettyPrint()}")
        else:
            print(f"Nombre cambiado en {router_ip}: {router_names[router_ip]}")
    except Exception as e:
        print(f"Error en {router_ip}: {str(e)}")
