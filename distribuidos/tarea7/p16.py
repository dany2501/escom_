from pysnmp.hlapi import *

# Definir los parámetros de autenticación SNMPv2
community = 'comunidad_snmp'  # Nombre de la comunidad SNMP

# Definir la dirección IP de cada router
routers = [
    '1.94.100.10',
    '1.94.100.11',
    # Agregar más direcciones IP de routers según sea necesario
]

# Definir el número de interfaz y la descripción a asignar
interface_description = {
    '1.0': 'Interfaz de red 1',
    '2.0': 'Interfaz de red 2',
    # Agregar más números de interfaz y descripciones según sea necesario
}

# Recorrer cada router y asignar la descripción a cada interfaz
for router_ip in routers:
    try:
        for if_number, if_description in interface_description.items():
            # Realizar una solicitud SNMP versión 2 para asignar la descripción a la interfaz del router
            error_indication, error_status, error_index, var_binds = next(
                setCmd(SnmpEngine(),
                       CommunityData(community),
                       UdpTransportTarget((router_ip, 161)),
                       ContextData(),
                       ObjectType(ObjectIdentity('IF-MIB', 'ifAlias', if_number), if_description)
                       )
            )

            if error_indication:
                print(f"Error en {router_ip} - Interfaz {if_number}: {error_indication}")
            elif error_status:
                print(f"Error en {router_ip} - Interfaz {if_number}: {error_status.prettyPrint()}")
            else:
                print(f"Descripción asignada en {router_ip} - Interfaz {if_number}: {if_description}")
    except Exception as e:
        print(f"Error en {router_ip}: {str(e)}")
