#include "unity.h"
#include "core.h"
#include "cardUtils.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_getCardStrength()
{
    Card card = {.color = SPADE, .value = SEVEN};
    int strength;
    strength = getCardStrength(card, NOTRUMP, NULL_COLOR);
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, strength, "SEVEN, NOTRUMP");
    strength = getCardStrength(card, CLUB, DIAMOND);
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, strength, "SEVEN, other colors");
    strength = getCardStrength(card, NULL_COLOR, SPADE);
    TEST_ASSERT_EQUAL_INT_MESSAGE(11, strength, "SEVEN, right color");
    strength = getCardStrength(card, SPADE, NULL_COLOR);
    TEST_ASSERT_EQUAL_INT_MESSAGE(19, strength, "SEVEN, trump");
    strength = getCardStrength(card, ALLTRUMP, NULL_COLOR);
    TEST_ASSERT_EQUAL_INT_MESSAGE(19, strength, "SEVEN, ALLTRUMP");
    strength = getCardStrength(card, SPADE, SPADE);
    TEST_ASSERT_EQUAL_INT_MESSAGE(29, strength, "SEVEN, right color and trump");
    card.value = JACK;
    card.color = CLUB;
    strength = getCardStrength(card, NULL_COLOR, CLUB);
    TEST_ASSERT_EQUAL_INT_MESSAGE(14, strength, "JACK, right color");
    strength = getCardStrength(card, CLUB, NULL_COLOR);
    TEST_ASSERT_EQUAL_INT_MESSAGE(28, strength, "JACK, trump");
    strength = getCardStrength(card, CLUB, CLUB);
    TEST_ASSERT_EQUAL_INT_MESSAGE(38, strength, "JACK, right color and trump");
}

void test_getStrongestCard()
{
    Card cardArraySingle[1] = {{.value = ACE, .color = HEART}};
    Card cardArrayTriple[4] =
        {{.value = SEVEN, .color = SPADE},
        { .value = JACK,  .color = HEART},
        { .value = QUEEN, .color = HEART},
        { .value = ACE,   .color = CLUB}};
    int strongestCard;
    strongestCard = getStrongestCard(cardArraySingle, 1, NULL_COLOR, NULL_COLOR);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, strongestCard, "Single card");
    strongestCard = getStrongestCard(cardArrayTriple, 4, NULL_COLOR, NULL_COLOR);
    TEST_ASSERT_EQUAL_INT_MESSAGE(3, strongestCard, "No strong colors");
    strongestCard = getStrongestCard(cardArrayTriple, 4, NULL_COLOR, SPADE);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, strongestCard, "Round color");
    strongestCard = getStrongestCard(cardArrayTriple, 4, NULL_COLOR, HEART);
    TEST_ASSERT_EQUAL_INT_MESSAGE(2, strongestCard, "Round color difference between JACK and QUEEN");
    strongestCard = getStrongestCard(cardArrayTriple, 4, HEART, CLUB);
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, strongestCard, "Round and trump color difference between JACK and QUEEN");
    strongestCard = getStrongestCard(cardArrayTriple, 4, ALLTRUMP, SPADE);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, strongestCard, "ALLTRUMP round color");
}

void test_sortCards()
{
    Card cardArray[4] =
        {{.value = EIGHT, .color = SPADE,   .canPlay = TRUE},
        { .value = NINE,  .color = DIAMOND, .canPlay = TRUE},
        { .value = QUEEN, .color = DIAMOND, .canPlay = TRUE},
        { .value = KING,  .color = CLUB,    .canPlay = TRUE}};
    Card cardArraySorted[4] =
        {{.value = EIGHT, .color = SPADE,   .canPlay = TRUE},
        { .value = NINE,  .color = DIAMOND, .canPlay = TRUE},
        { .value = QUEEN, .color = DIAMOND, .canPlay = TRUE},
        { .value = KING,  .color = CLUB,    .canPlay = TRUE}};
    Card cardArrayReverse[4] =
        {{.value = QUEEN, .color = DIAMOND, .canPlay = TRUE},
        { .value = KING,  .color = CLUB,    .canPlay = TRUE},
        { .value = NINE,  .color = DIAMOND, .canPlay = TRUE},
        { .value = EIGHT, .color = SPADE,   .canPlay = TRUE}};
    sortCards(cardArray, 4, NOTRUMP, NULL_COLOR);
    TEST_ASSERT_EQUAL_MEMORY_ARRAY_MESSAGE(cardArraySorted, cardArray, sizeof(Card), 4, "Already sorted");
    sortCards(cardArray, 4, ALLTRUMP, SPADE);
    TEST_ASSERT_EQUAL_MEMORY_ARRAY_MESSAGE(cardArrayReverse, cardArray, sizeof(Card), 4, "Reverse order (2-3-1-0)");
}

void test_removeCard()
{
    Card cardArrayToRemove[4] =
        {{.value = EIGHT, .color = SPADE},
        { .value = NINE,  .color = HEART},
        { .value = JACK,  .color = CLUB },
        { .value = ACE,   .color = SPADE}};
    Card cardArrayFirst[2] =
        {{.value = NINE,  .color = HEART},
        { .value = JACK,  .color = CLUB}};
    Card cardArrayMiddle[2] =
        {{.value = EIGHT, .color = SPADE},
        { .value = JACK,  .color = CLUB}};
    Card cardArrayLast[2] =
        {{.value = EIGHT, .color = SPADE},
        { .value = NINE,  .color = HEART}};
    Card *cardPointerArray[4] = {cardArrayFirst, cardArrayMiddle, cardArrayLast, cardArrayToRemove};
    int nbOfCards, nbOfElementsToCompare[4] = {2, 2, 2, 3};
    Bool foundCard, expectedFoundCard[4] = {TRUE, TRUE, TRUE, FALSE};
    char string[23];
    for (int i = 0; i <= 3; i++) {
        Card cardArray[3] =
            {{.value = EIGHT, .color = SPADE},
            { .value = NINE,  .color = HEART},
            { .value = JACK,  .color = CLUB}};
        nbOfCards = 3;
        foundCard = removeCard(cardArray, &nbOfCards, cardArrayToRemove[i]);
        sprintf(string, "%d: foundCard", i);
        TEST_ASSERT_TRUE_MESSAGE(foundCard == expectedFoundCard[i], string);
        sprintf(string, "%d: nbOfCards", i);
        TEST_ASSERT_EQUAL_INT_MESSAGE(nbOfCards, nbOfElementsToCompare[i], string);
        sprintf(string, "%d: Array after removal", i);
        TEST_ASSERT_EQUAL_MEMORY_ARRAY_MESSAGE(cardPointerArray[i], cardArray, sizeof(Card), nbOfElementsToCompare[i], string);
    }
}

void test_getPlayableCards()
{
    Card cardArray[2] =
        {{.value = EIGHT, .color = SPADE, .canPlay = TRUE},
        { .value = ACE,   .color = SPADE, .canPlay = TRUE}};
    Card cardArrayExpected[2] =
        {{.value = EIGHT, .color = SPADE, .canPlay = TRUE},
        { .value = ACE,   .color = SPADE, .canPlay = TRUE}};
    int nbOfPlayableCards;
    { Card playableCards[2];
    nbOfPlayableCards = getPlayableCards(cardArray, 2, playableCards);
    TEST_ASSERT_EQUAL_INT_MESSAGE(2, nbOfPlayableCards, "nbOfPlayableCards, canPlay both");
    TEST_ASSERT_EQUAL_MEMORY_ARRAY_MESSAGE(cardArrayExpected, playableCards, sizeof(Card), 2, "array, canPlay both");
    }
    { cardArray[1].canPlay = FALSE;
    Card playableCards[1];
    nbOfPlayableCards = getPlayableCards(cardArray, 2, playableCards);
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, nbOfPlayableCards, "nbOfPlayableCards, canPlay first");
    TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&(cardArrayExpected[0]), &(playableCards[0]), sizeof(Card), "array, canPlay first");
    }
    { cardArray[0].canPlay = FALSE;
    cardArray[1].canPlay = TRUE;
    Card playableCards[1];
    nbOfPlayableCards = getPlayableCards(cardArray, 2, playableCards);
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, nbOfPlayableCards, "nbOfPlayableCards, canPlay second");
    TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&(cardArrayExpected[1]), &(playableCards[0]), sizeof(Card), "array, canPlay second");
    }
}