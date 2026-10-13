#include "../XRInput.hpp"
#include "../BNMIncludes.hpp"
#include "../BNMResolve.hpp"
#include "../PhotonResolve.hpp"
#include "../httplib.h"
#include "../json.hpp"
#include "../XRInput.hpp"

class PlayerMods {
    public:static void invis() {
            Class cls = Class("Photon.Pun", "PhotonNetwork", Image("PhotonUnityNetworking"));
            if (cls.IsValid()) {
                Method<void> setname = cls.GetMethod("set_NickName", 1);
                if (setname.IsValid()) setname(CreateMonoString("__"));
            }
        }

            public:static void NIGGER() {
            Class cls = Class("Photon.Pun", "PhotonNetwork", Image("PhotonUnityNetworking"));
            if (cls.IsValid()) {
                Method<void> setname = cls.GetMethod("set_NickName", 1);
                if (setname.IsValid()) setname(CreateMonoString("NIGGER"));
            }
        }


public:static void rainbow() {
            Class cls = Class("Photon.Pun", "PhotonNetwork", Image("PhotonUnityNetworking"));
            if (cls.IsValid()) {
                Method<void> setname = cls.GetMethod("set_NickName", 1);
                if (setname.IsValid()) setname(CreateMonoString("RAYVO RUNS TS"));
            }
        }

        public:static void Error() {
            Class cls = Class("Photon.Pun", "PhotonNetwork", Image("PhotonUnityNetworking"));
            if (cls.IsValid()) {
                Method<void> setname = cls.GetMethod("set_NickName", 1);
                if (setname.IsValid()) setname(CreateMonoString("FUCK ALL YALL"));
            }
        }
    };