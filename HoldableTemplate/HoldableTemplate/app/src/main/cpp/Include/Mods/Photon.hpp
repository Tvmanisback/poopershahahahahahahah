#include "../XRInput.hpp"
#include "../BNMIncludes.hpp"
#include "../BNMResolve.hpp"
#include "../PhotonResolve.hpp"
#include "../httplib.h"
#include "../json.hpp"
#include "../XRInput.hpp"

class PhotonMods {
public:static void LeaveRoom()
    {
        Class photonClass = Class("Photon.Pun", "PhotonNetwork", Image("PhotonUnityNetworking"));

        Method<void *> disconnect = photonClass.GetMethod("Disconnect");
        if (disconnect.IsValid()) {
            disconnect();
        }
    }
};