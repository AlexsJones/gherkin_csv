Feature: Log into the app

  Scenario: When im signed in
    Given I am signed in
    When I do something
    Then something else happens

  Scenario Outline:
    Given this is a scenario Outline
    When I do <A>
    Then it works

    Examples:
      | A|
      | 1| 
