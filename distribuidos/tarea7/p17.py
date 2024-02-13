from pysnmp.hlapi import *

# Definir los parámetros de autenticación SNMPv2
community = 'comunidad_snmp'  # Nombre de la comunidad SNMP

# Definir la dirección IP y el número de interfaz para apagar
interfaces_to_shutdown = [
    {'router_ip': '1.94.100.10', 'interface': '2.0'},
    {'router_ip': '1.94.100.11', 'interface': '1.0'}
    # Agregar más direcciones IP y números de interfaz según sea necesario
]

# Recorrer cada interfaz y apagarla
for interface in interfaces_to_shutdown:
    try:
        # Realizar una solicitud SNMP versión 2 para apagar la interfaz del router
        error_indication, error_status, error_index, var_binds = next(
            setCmd(SnmpEngine(),
                   CommunityData(community),
                   UdpTransportTarget((interface['router_ip'], 161)),
                   ContextData(),
                   ObjectType(ObjectIdentity('IF-MIB', 'ifAdminStatus', interface['interface']), 2)
                   )
        )

        if error_indication:
            print(f"Error en {interface['router_ip']} - Interfaz {interface['interface']}: {error_indication}")
        elif error_status:
            print(f"Error en {interface['router_ip']} - Interfaz {interface['interface']}: {error_status.prettyPrint()}")
        else:
            print(f"Interfaz apagada en {interface['router_ip']} - Interfaz {interface['interface']}")
    except Exception as e:
        print(f"Error en {interface['router_ip']}: {str(e)}")
