from pysnmp.hlapi import *

# Definir los parámetros de autenticación SNMPv2
community = 'comunidad_snmp'  # Nombre de la comunidad SNMP

# Definir la dirección IP de cada router
routers = [
    '1.94.100.10',
    '1.94.100.11',
    # Agregar más direcciones IP de routers según sea necesario
]

# Recorrer cada router y obtener la lista de interfaces
for router_ip in routers:
    try:
        # Realizar una solicitud SNMP versión 2 para obtener la lista de interfaces del router
        error_indication, error_status, error_index, var_binds = next(
            nextCmd(SnmpEngine(),
                    CommunityData(community),
                    UdpTransportTarget((router_ip, 161)),
                    ContextData(),
                    ObjectType(ObjectIdentity('IF-MIB', 'ifDescr'))
                    )
        )

        if error_indication:
            print(f"Error en {router_ip}: {error_indication}")
        elif error_status:
            print(f"Error en {router_ip}: {error_status.prettyPrint()}")
        else:
            # Recorrer los resultados para obtener la lista de interfaces
            interfaces = []
            for var_bind in var_binds:
                interface_name = var_bind[1]
                interfaces.append(interface_name)

            print(f"Lista de interfaces del router en {router_ip}:")
            for interface in interfaces:
                print(interface)
    except Exception as e:
        print(f"Error en {router_ip}: {str(e)}")
