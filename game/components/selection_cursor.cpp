#include "selection_cursor.h"
#include "galaga.h"
#include "game.h"
#include "input_locator.h"
#include "nMath.h"
#include "ntime.h"
#include "text_component.h"
#include <cmath>
#include <utility>

using namespace nim;
using namespace galaga;

SelectionCursor::SelectionCursor() : elementNames{} {
    name = "SelectionCursor";
    transform = nullptr;
    input = InputLocator::GetInput();
}

SelectionCursor::SelectionCursor(std::vector<std::string> elements) : elementNames{std::move(elements)} {
    name = "SelectionCursor";
    transform = nullptr;
    input = InputLocator::GetInput();
}

SelectionCursor::SelectionCursor(const SelectionCursor &other) {
    name = other.name;
    transform = other.transform;
    elementNames = other.elementNames;
    elementReferences = other.elementReferences;
    input = other.input;
}

SelectionCursor::SelectionCursor(SelectionCursor &&other) noexcept {
    name = std::move(other.name);
    transform = other.transform;
    elementNames = std::move(other.elementNames);
    elementReferences = std::move(other.elementReferences);
    input = other.input;

    other.transform = nullptr;
    other.input = nullptr;
}

SelectionCursor::~SelectionCursor() {
    transform = nullptr;
}

SelectionCursor &SelectionCursor::operator=(const SelectionCursor &other) {
    if (&other != this) {
        name = other.name;
        transform = other.transform;
        elementNames = other.elementNames;
        elementReferences = other.elementReferences;
        input = other.input;
    }

    return *this;
}

SelectionCursor &SelectionCursor::operator=(SelectionCursor &&other) noexcept {
    if (&other != this) {
        name = std::move(other.name);
        transform = other.transform;
        elementNames = std::move(other.elementNames);
        elementReferences = std::move(other.elementReferences);
        input = other.input;

        other.transform = nullptr;
        other.input = nullptr;
    }

    return *this;
}
void SelectionCursor::Init() {
    for (const auto &element: elementNames) {
        auto found = Game::Find(element);
        elementReferences.emplace_back(found);
    }

    currentIndex = 0;
    auto tc = elementReferences[currentIndex]->GetComponent<TextComponent>("TextComponent");
    colorCache = tc->GetColor();
    tc->SetColor(Red);

    select = parent->GetComponent<nim::SoundComponent<nim::Sound>>("SoundComponent");
}
void SelectionCursor::Update() {
    auto tc = elementReferences[currentIndex]->GetComponent<TextComponent>("TextComponent");
    channelValue = Lerp(channelValue, 1, t);
    Color newColor = tc->GetColor();

    if (prepareForTransition)
        newColor.A = ToIntColorChannel(channelValue);
    else
        newColor.B = ToIntColorChannel(channelValue);

    tc->SetColor(newColor);
    if (channelValue > 0.95) channelValue = 0;

    if (input->GetKeyUp(Key::UP)) {
        NextElement(-1);
    }

    if (input->GetKeyUp(Key::DOWN)) {
        NextElement(1);
    }

    if (input->GetKeyUp(Key::ENTER)) {
        if (currentIndex == 0) {
            if (select != nullptr) {
                select->Load("start_level");
                select->Play();
                prepareForTransition = true;
                t = 0.5f;
            }
        }
        if (currentIndex == elementReferences.size() - 1)
            InputLocator::GetInput()->onExitGameEvent.Invoke(false);
    }

    if (prepareForTransition && !select->sound.IsPlaying()) {
        Galaga::Instance().LoadScene(SceneManager::NextScene());
    }
}
void SelectionCursor::NextElement(int newIndex) {
    auto tc = elementReferences[currentIndex]->GetComponent<TextComponent>("TextComponent");
    tc->SetColor(colorCache);
    currentIndex = std::abs(currentIndex + newIndex) % static_cast<int>(elementReferences.size());
    tc = elementReferences[currentIndex]->GetComponent<TextComponent>("TextComponent");
    colorCache = tc->GetColor();
    tc->SetColor(Red);

    if (select != nullptr)
        select->Play();
}
