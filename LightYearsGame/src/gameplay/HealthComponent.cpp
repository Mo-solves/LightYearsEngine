#include "gameplay/HealthComponent.h"
#include "framework/Core.h"

namespace ly
{
	HealthComponent::HealthComponent(float health, float maxHealth)
		: mHealth{ health },
		mMaxHealth{maxHealth}
	{
	}

	void HealthComponent::ChangeHealth(float amt)
	{
		if (amt == 0) return;
		if (mHealth == 0) return;

		mHealth += amt;

		if (mHealth < 0)
		{
			mHealth = 0;
		}

		if (mHealth > mMaxHealth)
		{
			mHealth = mMaxHealth;
		}

		if (amt < 0)
		{
			TakenDamage(-amt);
			if (mHealth <= 0)
			{
				HealthEmpty();
			}
		}
		onHealthChanged.BroadCast(amt, mHealth, mMaxHealth);
	}

	void HealthComponent::TakenDamage(float amt)
	{
		onTakeDamage.BroadCast(amt, mHealth, mMaxHealth);
	}

	void HealthComponent::HealthEmpty()
	{
		onHealthEmpty.BroadCast();
	}
}