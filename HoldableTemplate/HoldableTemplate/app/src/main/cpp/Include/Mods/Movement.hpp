#include "../XRInput.hpp"
#include "../BNMIncludes.hpp"
#include "../BNMResolve.hpp"
#include "../PhotonResolve.hpp"
#include "../httplib.h"
#include "../json.hpp"
#include "../XRInput.hpp"

class Movement{
public: static void HeadFly()
    {
        // Right controller plate
        static GameObject* rightPlat = nullptr;
        bool rightGrip = XRInput::GetBoolFeature(BoolFeature::GripButton, Controller::Right);

        if (rightGrip)
        {
            if (rightPlat == nullptr)
            {
                // Get right controller position
                GameObject* rightController = GameObject::Find("RightHand Controller");
                if (rightController)
                {
                    rightPlat = GameObject::CreatePrimitive(PrimitiveType::Cube);
                    Vector3 controllerPos = rightController->GetTransform()->GetPosition();
                    Vector3 platPos = Vector3(controllerPos.x, controllerPos.y - 0.1f, controllerPos.z);

                    rightPlat->GetTransform()->SetPosition(platPos);  // Fixed typo: SetPostion -> SetPosition
                    rightPlat->GetTransform()->SetLocalScale(Vector3(0.289351f, 0.03870832f, 0.4166668f));
                }
            }
        }
        else
        {
            if (rightPlat != nullptr)
            {
                GameObject::Destroy(rightPlat);
                rightPlat = nullptr;
            }
        }

        // Left controller plate
        static GameObject* leftPlat = nullptr;
        bool leftGrip = XRInput::GetBoolFeature(BoolFeature::GripButton, Controller::Left);

        if (leftGrip)
        {
            if (leftPlat == nullptr)
            {
                GameObject* leftController = GameObject::Find("LeftHand Controller");
                if (leftController)
                {
                    leftPlat = GameObject::CreatePrimitive(PrimitiveType::Cube);
                    Vector3 controllerPos = leftController->GetTransform()->GetPosition();
                    Vector3 platPos = Vector3(controllerPos.x, controllerPos.y - 0.1f, controllerPos.z);

                    leftPlat->GetTransform()->SetPosition(platPos);
                    leftPlat->GetTransform()->SetLocalScale(Vector3(0.4f, 0.05f, 0.4f));
                }
            }
        }
        else
        {
            if (leftPlat != nullptr)
            {
                GameObject::Destroy(leftPlat);
                leftPlat = nullptr;
            }
        }
    }

public:
    static void platforms() {
        static GameObject *platR = nullptr;
        static GameObject *platL = nullptr;

        bool rightGrab = XRInput::GetBoolFeature(BoolFeature::GripButton, Controller::Right);
        bool leftGrab  = XRInput::GetBoolFeature(BoolFeature::GripButton, Controller::Left);

        auto createPlatform = [](char *handName) -> GameObject * {
            GameObject *plat = GameObject::CreatePrimitive(PrimitiveType::Cube);

            Renderer *renderer = (Renderer *)plat->GetComponent(Renderer::GetType());
            if (renderer) {
                Material *mat = renderer->GetMaterial();
                if (mat) {
                    mat->SetShader(Shader::Find("Standard"));
                    mat->SetColor(Settings::backgroundColor);
                }
            }

            Transform *handTransform = GameObject::Find(handName)->GetTransform();
            plat->GetTransform()->SetLocalScale(Vector3(0.025f, 0.3f, 0.4f));
            plat->GetTransform()->SetLocalPosition(
                    handTransform->GetPosition() + Vector3(0.0f, -0.07f, 0.0f));
            plat->GetTransform()->SetLocalRotation(handTransform->GetRotation());

            return plat;
        };

        auto destroyPlatform = [](GameObject *plat) {
            if (!plat) return;
            plat->AddComponent(Rigidbody::GetType());
            GameObject::Destroy(plat->GetComponent(Collider::GetType()));
            GameObject::Destroy(plat, 2.0f);
        };

        if (leftGrab) {
            if (!platL) platL = createPlatform("LeftHand Controller");
        } else if (platL) {
            destroyPlatform(platL);
            platL = nullptr;
        }

        if (rightGrab) {
            if (!platR) platR = createPlatform("RightHand Controller");
        } else if (platR) {
            destroyPlatform(platR);
            platR = nullptr;
        }
    }


public:static void FixArms()
    {
        GameObject::Find("GorillaPlayer")->GetTransform()->SetLocalScale(Vector3(1.0f, 1.0f, 1.0f));
    }

public:static void Longarms(bool active) {
        if (active)
        {
            GameObject::Find("GorillaPlayer")->GetTransform()->SetLocalScale(Vector3(1.5f, 1.5f, 1.5f));
        }
        else
        {
            GameObject::Find("GorillaPlayer")->GetTransform()->SetLocalScale(Vector3(1.0f, 1.0f, 1.0f));
        }
    }


public:static void HandFly()
    {
        float trigR = XRInput::GetFloatFeature(FloatFeature::Trigger, Controller::Right);
        if (trigR > 0.5f) {
            Transform *handR = GameObject::Find("RightHand Controller")->GetTransform();
            Rigidbody *rigidbody = (Rigidbody *) GameObject::Find("GorillaPlayer")->GetComponent(
                    Rigidbody::GetType());
            Vector3 force = handR->GetForward() * 15.0f;
            rigidbody->SetVelocity(force);
        }
    }

public:static void Car()
    {
        float trigR = XRInput::GetFloatFeature(FloatFeature::Trigger, Controller::Right);
        if (trigR > 0.5f) {
            Transform *Cam = GameObject::Find("Main Camera")->GetTransform();
            Rigidbody *rigidbody = (Rigidbody *) GameObject::Find("GorillaPlayer")->GetComponent(
                    Rigidbody::GetType());
            Vector3 Camforce = Cam->GetForward() * 15.0f;
            Vector3 force = Vector3(Camforce.x, 0.0f, Camforce.z);
            rigidbody->SetVelocity(Camforce);
        }
    }
public:static void SlingshotFly()
    {
        float trigR = XRInput::GetFloatFeature(FloatFeature::Trigger, Controller::Right);
        if (trigR > 0.5f) {
            Transform *handR = GameObject::Find("RightHand Controller")->GetTransform();
            Rigidbody *rigidbody = (Rigidbody *) GameObject::Find("GorillaPlayer")->GetComponent(Rigidbody::GetType());
            Vector3 force = handR->GetForward() * 1.0f;
            rigidbody->AddForce(force, ForceMode::VelocityChange);
        }
    }
public:static void UpAndDown(bool active)
    {

        if (!active)
        {
            return;
        }

        Vector3 Up(Vector3(0, 1, 0));
        Vector3 Down(Vector3(0, -1, 0));

        float trigR = XRInput::GetFloatFeature(FloatFeature::Trigger, Controller::Right);
        float trigL = XRInput::GetFloatFeature(FloatFeature::Trigger, Controller::Left);
        Rigidbody *rigidbody = (Rigidbody *) GameObject::Find("GorillaPlayer")->GetComponent(Rigidbody::GetType());

        if (trigR > 0.5f)
        {
            rigidbody->AddForce(Up, ForceMode::VelocityChange);
        }
        if (trigL > 0.5f)
        {
            rigidbody->AddForce(Down, ForceMode::VelocityChange);
        }
    }
};