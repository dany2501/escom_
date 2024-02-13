from pysnmp.hlapi import *

# Definir los parámetros de autenticación SNMPv2
community = 'comunidad_snmp'  # Nombre de la comunidad SNMP

# Definir la dirección IP de cada router
routers = [
    '1.94.100.10',
    '1.94.100.11',
    # Agregar más direcciones IP de routers según sea necesario
]

# Recorrer cada router y obtener su nombre
for router_ip in routers:
    try:
        # Realizar una solicitud SNMP versión 2 para obtener el nombre del router
        error_indication, error_status, error_index, var_binds = next(
            getCmd(SnmpEngine(),
                   CommunityData(community),
                   UdpTransportTarget((router_ip, 161)),
                   ContextData(),
                   ObjectType(ObjectIdentity('SNMPv2-MIB', 'sysName', 0))
                   )
        )

        if error_indication:
            print(f"Error en {router_ip}: {error_indication}")
        elif error_status:
            print(f"Error en {router_ip}: {error_status.prettyPrint()}")
        else:
            # Obtener el valor del nombre del router desde la respuesta SNMP
            for var_bind in var_binds:
                router_name = var_bind[1]
                print(f"Nombre del router en {router_ip}: {router_name}")
    except Exception as e:
        print(f"Error en {router_ip}: {str(e)}")
