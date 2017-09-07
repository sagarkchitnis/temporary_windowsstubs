#ifndef __AGENT_CONSTANTS_H__
#define __AGENT_CONSTANTS_H__

#include<string>

class AgentConstants
{
public:
    static const std::string contrail_collector_log ; // "/var/log/contrail/contrail-collector.log"
    static const std::string contrail_named_log ; // "/var/log/contrail/contrail-named.log"
    static const std::string named_bind_log ; // "/var/log/named/bind.log"
    static const std::string contrail_control_log ; // "/var/log/contrail/contrail-control.log"
    static const std::string contrail_dns_log ; // "/var/log/contrail/contrail-dns.log"
    static const std::string log_dns ; // "/var/log/dns"
    static const std::string contrail_query_engine_log ; // "/var/log/contrail/contrail-query-engine.log"
    static const std::string contrail_vrouter2_log ; // "/var/log/contrail/vrouter2.log"
    static const std::string contrail_control_conf ; // "/etc/contrail/contrail-control.conf"
    static const std::string contrail_ssl_certs_server_pem ; // "/etc/contrail/ssl/certs/server.pem"
    static const std::string contrail_ssl_server_privkey_pem ; // "/etc/contrail/ssl/private/server-privkey.pem"
    static const std::string contrail_ssl_certs_ca_cert_pem ; // "/etc/contrail/ssl/certs/ca-cert.pem"
    static const std::string server_pem ; // "/etc/server.pem"
    static const std::string server_key ; // "/etc/server.key"
    static const std::string ca_cert_pem ; // "/etc/ca-cert.pem"
    static const std::string resolv_conf ; // "/etc/resolv.conf"
    static const std::string contrail_dns_conf ; // "/etc/contrail/contrail-dns.conf"
    static const std::string contrail_dns ; // "/etc/contrail/dns"
    static const std::string contrail_dns_named_log ; // "/etc/contrail/dns/named.log"
    static const std::string server_privkey_pem ; // "/etc/server-privkey.pem\n"
    static const std::string contrail_dns_test_dir ; // "/etc/contrail/dns/test"
    static const std::string contrail_query_engine_conf ; // "/etc/contrail/contrail-query-engine.conf"
};

#endif // __AGENT_CONSTANTS_H__
