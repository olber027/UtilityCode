//
// Created by molberding on 10/18/2017.
//

#ifndef UTILITYCODE_REGEX_H
#define UTILITYCODE_REGEX_H

#include "SmartString.h"
#include <vector>

using namespace smart_string;

namespace regex {

    template<typename T>
    class Match {
    private:
        SmartString matchingPattern;
        int index;
    public:
        Match() : matchingPattern(""), index(-1) {}
        Match(const T& pattern, const int idx) : matchingPattern(pattern), index(idx) {}

        T getPattern() const {
            return (T) matchingPattern;
        }
        int getPatternIndex() const {
            return index;
        }
    };

    template<typename T>
    class Regex {
    private:

        class State {
        private:
            std::vector<State*> nextPossibleStates;
            SmartString matchingCriteria;
            bool end;
        public:

            State() : nextPossibleStates(std::vector<State*>()), matchingCriteria(""), end(false) {}
            template<typename U>
            State(const U& criteria) : nextPossibleStates(std::vector<State*>()), matchingCriteria(criteria), end(false) {}
            template<typename U>
            State(const U& criteria, const bool End) : nextPossibleStates(std::vector<State*>()), matchingCriteria(criteria), end(End) {}

            void addNextState(State* nextState) {
                nextPossibleStates.push_back(nextState);
                end = false;
            }

            void addNextStates(std::vector<State*> nextStates) {
                for(int i = 0; i < nextStates.size(); i++) {
                    nextPossibleStates.push_back(nextStates[i]);
                }
                end = false;
            }

            std::vector<State*> advance(char c) {
                std::vector<State*> nextStates = std::vector<State*>();
                for(int i = 0; i < nextPossibleStates.size(); i++) {
                    if(nextPossibleStates[i]->matchingCriteria == "" ||
                       nextPossibleStates[i]->matchingCriteria.contains(c)) {
                        nextStates.push_back(nextPossibleStates[i]);
                    }
                }
                return nextStates;
            }

            void makeEnd() {
                end = true;
            }

            bool isEnd() const {
                return end;
            }
        };

        class PossibleMatch {
        private:
            SmartString currentContents;
            State* currentState;
            int startingIndex;
        public:
            PossibleMatch(const SmartString& contents, State* state, const int index) :
                    currentContents(contents), currentState(state), startingIndex(index) {}
            State* getState() const {
                return currentState;
            }
            SmartString getContents() const {
                return currentContents;
            }
            int getStartingIndex() const {
                return startingIndex;
            }
        };

        bool isCompiled;
        SmartString pattern;
        State* initialState;

        // turns the given string into one or more strings, separated by the
        // outermost OR characters. e.g. a|b|c would turn into ["a","b","c"],
        // (a|b)|c would turn into ["(a|b)", "c"], and "ab" would turn into
        // ["ab"].
        std::vector<SmartString> separateOrClauses(SmartString& str) {
            std::vector<SmartString> resultStrings;
            SmartString currentString;
            int parenCount = 0;
            int index = 0;

            while(index < str.length()) {
                if(str[index] == '(') {
                    parenCount++;
                    currentString << str[index];
                } else if(str[index] == ')') {
                    parenCount--;
                    currentString << str[index];
                } else if(str[index] == '|' && parenCount <= 0) {
                    resultStrings.push_back(currentString);
                    currentString = "";
                } else {
                    currentString << str[index];
                }
                index++;
            }

            if(currentString != "") {
                resultStrings.push_back(currentString);
            }

            return resultStrings;
        }

        std::vector<State*> parse(SmartString& str) {
            std::vector<SmartString> strings = separateOrClauses(str);
            std::vector<State*> states;

            for(int i = 0; i < strings.size(); i++) {
                SmartString string = strings[i];
                int index = 0;
                std::vector<State*> currentStates;

                while(index < string.length()) {
                    std::vector<State*> resultStates;
                    if(string[index] == '(') {
                        int parenCount = 0;
                        index++;
                        SmartString substr;
                        while(string[index] != ')' || parenCount != 0) {
                            substr << string[index];
                            if(string[index] == '(') {
                                parenCount++;
                            } else if(string[index] == ')') {
                                parenCount--;
                            }
                            index++;
                        }
                        std::vector<State*> substrResults = parse(substr);
                        for(int j = 0; j < substrResults.size(); j++) {
                            resultStates.push_back(substrResults[j]);
                        }
                    } else {
                        resultStates.push_back(new State(string[index]));
                    }

                    if(currentStates.size() == 0) {
                        for(int j = 0; j < resultStates.size(); j++) {
                            states.push_back(resultStates[j]);
                        }
                    }

                    for(int j = 0; j < currentStates.size(); j++) {
                        currentStates[j]->addNextStates(resultStates);
                    }
                    currentStates = resultStates;
                    index++;
                }
                for(int j = 0; j < currentStates.size(); j++) {
                    currentStates[j]->makeEnd();
                }
            }
            return states;
        }

    public:

        Regex() : isCompiled(false), pattern(""), initialState(nullptr) {}
        template<typename U>
        Regex(const U& Pattern, const bool doCompilation) : Regex() {
            pattern = Pattern;
            if(doCompilation) {
                isCompiled = compile();
            }
            if(!isCompiled) {
                initialState = nullptr;
            }
        }
        template<typename U>
        Regex(const U& Pattern) : Regex(pattern, true) {}

        template<typename U>
        bool compile(const U& Pattern) {
            pattern = Pattern;
            return compile();
        }

        bool compile() {
            if(pattern == "") {
                isCompiled = false;
                return false;
            }

            if(initialState != nullptr) {
                delete initialState;
            }

            initialState = new State();
            initialState->addNextStates(parse(pattern));
            isCompiled = true;

            return true;
        }

        template<typename U>
        Match<T> firstMatch(const U& text) {
            SmartString str = text;
            std::vector<PossibleMatch> currentPossibleMatches;
            std::vector<PossibleMatch> nextPossibleMatches = std::vector<PossibleMatch>();
            std::vector<Match<T>> matches = std::vector<Match<T>>();

            if(!isCompiled) {
                compile();
            }

            for(int i = 0; i < str.length(); i++) {
                currentPossibleMatches = nextPossibleMatches;
                nextPossibleMatches = std::vector<PossibleMatch>();

                std::vector<State*> nextStates = initialState->advance(str[i]);
                for(int k = 0; k < nextStates.size(); k++) {
                    nextPossibleMatches.push_back(PossibleMatch(str[i], nextStates[k], i));
                }

                for(int j = 0; j < currentPossibleMatches.size(); j++) {
                    PossibleMatch currentMatch = currentPossibleMatches[j];
                    if(currentMatch.getState()->isEnd()) {
                        return Match<T>(currentMatch.getContents(), currentMatch.getStartingIndex());
                    }
                    nextStates = currentMatch.getState()->advance(str[i]);
                    for(int k = 0; k < nextStates.size(); k++) {
                        nextPossibleMatches.push_back(
                                PossibleMatch(
                                        currentMatch.getContents().append(str[i]),
                                        nextStates[k],
                                        currentMatch.getStartingIndex()
                                )
                        );
                    }
                }
            }

            for(int i = 0; i < currentPossibleMatches.size(); i++) {
                PossibleMatch currentMatch = currentPossibleMatches[i];
                if(currentMatch.getState()->isEnd()) {
                    return Match<T>(currentMatch.getContents(), currentMatch.getStartingIndex());
                }
            }

            return Match<T>("", -1);
        }

        template<typename U>
        std::vector<Match<T>> matchAll(const U& text) {
            SmartString str = text;
            std::vector<PossibleMatch> currentPossibleMatches;
            std::vector<PossibleMatch> nextPossibleMatches;
            std::vector<Match<T>> matches = std::vector<Match<T>>();

            if(!isCompiled) {
                compile();
            }

            for(int i = 0; i < str.length(); i++) {
                currentPossibleMatches = nextPossibleMatches;
                nextPossibleMatches = std::vector<PossibleMatch>();

                std::vector<State*> nextStates = initialState->advance(str[i]);
                for(int j = 0; j < nextStates.size(); j++) {
                    nextPossibleMatches.push_back(PossibleMatch(str[i], nextStates[j], i));
                }

                for(int j = 0; j < currentPossibleMatches.size(); j++) {
                    PossibleMatch currentMatch = currentPossibleMatches[j];
                    if(currentMatch.getState()->isEnd()) {
                        matches.push_back(Match<T>(currentMatch.getContents(), currentMatch.getStartingIndex()));
                        continue;
                    }
                    nextStates = currentMatch.getState()->advance(str[i]);
                    for(int k = 0; k < nextStates.size(); k++) {
                        nextPossibleMatches.push_back(
                                PossibleMatch(
                                        currentMatch.getContents().append(str[i]),
                                        nextStates[k],
                                        currentMatch.getStartingIndex()
                                )
                        );
                    }
                }
            }

            for(int i = 0; i < nextPossibleMatches.size(); i++) {
                PossibleMatch currentMatch = nextPossibleMatches[i];
                if(currentMatch.getState()->isEnd()) {
                    matches.push_back(Match<T>(currentMatch.getContents(), currentMatch.getStartingIndex()));
                }
            }

            return matches;
        }

        template<typename U>
        Match<T> match(const U& text) {
            std::vector<Match<T>> matches = matchAll(text);
            Match<T> longestMatch;
            for(int i = 0; i < matches.size(); i++) {
                if(longestMatch.getPattern().length() < matches[i].getPattern().length()) {
                    longestMatch = matches[i];
                }
            }
            return longestMatch;
        }
    };
}
#endif //UTILITYCODE_REGEX_H
