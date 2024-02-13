from pysnmp.hlapi import *

# Definir los parámetros de autenticación SNMPv2
community = 'comunidad_snmp'  # Nombre de la comunidad SNMP

# Definir la dirección IP de cada router
routers = [
    '1.94.100.10',
    '1.94.100.11',
    # Agregar más direcciones IP de routers según sea necesario
]

# Recorrer cada router y obtener la lista de direcciones IP
for router_ip in routers:
    try:
        # Realizar una solicitud SNMP versión 2 para obtener la lista de direcciones IP del router
        error_indication, error_status, error_index, var_binds = next(
            nextCmd(SnmpEngine(),
                    CommunityData(community),
                    UdpTransportTarget((router_ip, 161)),
                    ContextData(),
                    ObjectType(ObjectIdentity('IP-MIB', 'ipAdEntAddr'))
                    )
        )

        if error_indication:
            print(f"Error en {router_ip}: {error_indication}")
        elif error_status:
            print(f"Error en {router_ip}: {error_status.prettyPrint()}")
        else:
            # Recorrer los resultados para obtener la lista de direcciones IP
            ip_addresses = []
            for var_bind in var_binds:
                ip_address = var_bind[1]
                ip_addresses.append(ip_address)

            print(f"Lista de direcciones IP del router en {router_ip}:")
            for ip_address in ip_addresses:
                print(ip_address)
    except Exception as e:
        print(f"Error en {router_ip}: {str(e)}")
