from pysnmp.hlapi import *

# Definir los parámetros de autenticación SNMPv2
community = 'comunidad_snmp'  # Nombre de la comunidad SNMP

# Definir la dirección IP y el nuevo nombre de cada router
routers = [
    {'ip': '1.94.100.10', 'new_name': 'R1'},
    {'ip': '1.94.100.11', 'new_name': 'R2'}
    # Agregar más direcciones IP y nuevos nombres de router según sea necesario
]

# Recorrer cada router y cambiar su nombre
for router in routers:
    try:
        # Realizar una solicitud SNMP versión 2 para cambiar el nombre del router
        error_indication, error_status, error_index, var_binds = next(
            setCmd(SnmpEngine(),
                   CommunityData(community),
                   UdpTransportTarget((router['ip'], 161)),
                   ContextData(),
                   ObjectType(ObjectIdentity('SNMPv2-MIB', 'sysName', 0), router['new_name'])
                   )
        )

        if error_indication:
            print(f"Error en {router['ip']}: {error_indication}")
        elif error_status:
            print(f"Error en {router['ip']}: {error_status.prettyPrint()}")
        else:
            print(f"Nombre del router cambiado en {router['ip']}")
    except Exception as e:
        print(f"Error en {router['ip']}: {str(e)}")
