Feature: Log into the app

  Scenario: I want to sign in
    Given the anonymous library screen is displayed
    When I sign in
    Then I should be on the user library screen

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
