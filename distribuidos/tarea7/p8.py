from pysnmp.hlapi import *

# Definir los parámetros de autenticación SNMPv3
username = 'userAsr'
password = 'pswAsr'
auth_protocol = usmHMACSHAAuthProtocol  # Protocolo de autenticación (usmHMACMD5AuthProtocol o usmHMACSHAAuthProtocol)
privacy_protocol = usmAesCfb128Protocol  # Protocolo de privacidad (usmDESPrivProtocol o usmAesCfb128Protocol)
auth_key = 'claveASR'  # Clave de autenticación (contraseña o frase)
privacy_key = 'claveASRPrivate'  # Clave de privacidad (contraseña o frase)

# Definir la dirección IP y la interfaz a apagar en cada router
routers = [
    {
        'ip': '1.94.100.10',
        'interface': 'Gi2/0'
    },
    {
        'ip': '1.94.100.11',
        'interface': 'Gi1/0'
    }
]

# Recorrer cada router y apagar la interfaz especificada
for router in routers:
    try:
        # Apagar la interfaz
        error_indication, error_status, error_index, var_binds = next(
            setCmd(SnmpEngine(),
                   UsmUserData(username, auth_key, privacy_key,
                               authProtocol=auth_protocol,
                               privProtocol=privacy_protocol),
                   UdpTransportTarget((router['ip'], 161)),
                   ContextData(),
                   ObjectType(ObjectIdentity('IF-MIB', 'ifAdminStatus', router['interface'])).set(2)  # 2 es el valor para apagar la interfaz
                   )
        )

        if error_indication:
            print(f"Error en {router['ip']}: {error_indication}")
        elif error_status:
            print(f"Error en {router['ip']}: {error_status.prettyPrint()}")
        else:
            print(f"Interfaz {router['interface']} apagada en {router['ip']}")

        # Configurar la interfaz para evitar cambios mediante SNMP
        error_indication, error_status, error_index, var_binds = next(
            setCmd(SnmpEngine(),
                   UsmUserData(username, auth_key, privacy_key,
                               authProtocol=auth_protocol,
                               privProtocol=privacy_protocol),
                   UdpTransportTarget((router['ip'], 161)),
                   ContextData(),
                   ObjectType(ObjectIdentity('IF-MIB', 'ifStackStatus', router['interface'])).set(2)  # 2 es el valor para evitar cambios mediante SNMP
                   )
        )

        if error_indication:
            print(f"Error en la configuración de la interfaz en {router['ip']}: {error_indication}")
        elif error_status:
            print(f"Error en la configuración de la interfaz en {router['ip']}: {error_status.prettyPrint()}")
        else:
            print(f"Configuración de la interfaz {router['interface']} actualizada en {router['ip']}")
    except Exception as e:
        print(f"Error en {router['ip']}: {str(e)}")
