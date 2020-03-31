#ifndef CASBIN_CPP_RBAC_GROUP_ROLE_MANAGER
#define CASBIN_CPP_RBAC_GROUP_ROLE_MANAGER

#include "DefaultRoleManager.h"

using namespace std;

/**
 * GroupRoleManager is used for authorization if the user's group is the role who has permission,
 * but the group information is in the default format (policy start with "g") and the role information
 * is in named format (policy start with "g2", "g3", ...).
 * e.g.
 * p, admin, domain1, data1, read
 * g, alice, group1
 * g2, group1, admin, domain1
 *
 * As for the previous example, alice should have the permission to read data1, but if we use the
 * DefaultRoleManager, it will return false.
 * GroupRoleManager is to handle this situation.
 */
class GroupRoleManager : public DefaultRoleManager {
    public:
        /**
         * GroupRoleManager is the constructor for creating an instance of the
         * GroupRoleManager implementation.
         *
         * @param maxHierarchyLevel the maximized allowed RBAC hierarchy level.
         */
        static GroupRoleManager* NewGroupRoleManager(int maxHierarchyLevel){
            return (GroupRoleManager*)NewRoleManager(maxHierarchyLevel);
        }

        /**
         * hasLink determines whether role: name1 inherits role: name2.
         * domain is a prefix to the roles.
         */
        bool HasLink(string name1, string name2, vector <string> domain) {
            if(DefaultRoleManager :: HasLink(name1, name2, domain)) {
                return true;
            }
            unsigned int domain_length = sizeof(domain)/sizeof(domain[0]);
            // check name1's groups
            if (domain_length == 1) {
                try {
                    vector <string> domain1;
                    vector <string> groups = DefaultRoleManager :: GetRoles(name1, domain1);
                    for(vector <string> :: iterator group = groups.begin() ; group < groups.end() ; group++) {
                        if(DefaultRoleManager :: HasLink(*group, name2, domain)) {
                            return true;
                        }
                    }
                } catch (CasbinRBACException ignore) {
                    return false;
                }
            }
            return false;
        }
};

#endif