from pysnmp.hlapi import *

def obtener_tiempo_funcionamiento(ip, puerto, comunidad, usuario, clave):
    engine = SnmpEngine()

    auth_protocol = usmHMACSHAAuthProtocol
    priv_protocol = usmAesCfb128Protocol

    auth_data = UsmUserData(
        userName=usuario,
        authKey=clave,
        authProtocol=auth_protocol,
        privKey=clave,
        privProtocol=priv_protocol
    )

    target = UdpTransportTarget((ip, puerto))
    error_indication, error_status, error_index, var_binds = next(
        getCmd(
            engine,
            auth_data,
            target,
            ContextData(),
            ObjectType(ObjectIdentity('SNMPv2-MIB', 'sysUpTime', 0))
        )
    )

    if error_indication:
        print('Error:', error_indication)
    elif error_status:
        print('Error:', error_status, error_index, var_binds)
    else:
        for var_bind in var_binds:
            oid = var_bind[0]
            value = var_bind[1]
            print(f'Tiempo de funcionamiento: {value.prettyPrint()}')

obtener_tiempo_funcionamiento('1.94.200.10', 161, 'public', 'usuario', 'clave')