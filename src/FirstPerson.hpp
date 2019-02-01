#pragma once

#include <chrono>

#include "Mod.hpp"
#include "Patch.hpp"

class FirstPerson : public Mod {
public:
    FirstPerson();

    void onFrame() override;
    void onDrawUI() override;
    void onComponent(REComponent* component) override;
    void onUpdateTransform(RETransform* transform) override;

protected:
    // gross
    bool listBoxHandlerAttach(void* data, int idx, const char** outText) {
        *outText = ((decltype(m_attachNames)*)data)->at(idx).data();
        return true;
    }

private:
    void reset();
    bool updatePointersFromCameraSystem(RopewayCameraSystem* cameraSystem);
    void updateCameraTransform(RETransform* transform);
    void updatePlayerTransform(RETransform* transform);
    float updateDeltaTime(RETransform* transform);

    std::string m_attachBoneImgui{ "head" };
    std::wstring m_attachBone{ L"head" };
    std::string m_playerName{ "pl1000" };

    // Different "configs" for each model
    std::unordered_map<std::string, Vector4f> m_attachOffsets;
    Matrix4x4f m_rotationOffset{ glm::identity<Matrix4x4f>() };
    Matrix4x4f m_lastBoneRotation{ glm::identity<Matrix4x4f>() };
    Matrix4x4f m_lastCameraMatrix{ glm::identity<Matrix4x4f>() };

    float m_scale{ 30.0f };
    float m_boneScale{ 15.0f };

    RETransform* m_playerTransform{ nullptr };
    RECamera* m_camera{ nullptr };
    RECamera* m_playerCameraController{ nullptr };
    RopewayCameraSystem* m_cameraSystem{ nullptr };

    bool m_enabled{ true };
    bool m_inEventCamera{ false };
    bool m_resetView{ false };

    std::unordered_map<RETransform*, std::chrono::high_resolution_clock::time_point> m_updateTimes;

    std::vector<std::string> m_attachNames;
    int32_t m_attachSelected{ 0 };

    // Allows us to freely modify the real camera position
    // which is used for firing weapons among other things
    std::unique_ptr<Patch> m_cameraControllerPosPatch{};
};