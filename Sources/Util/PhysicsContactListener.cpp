#include <box2d/box2d.h>

#include <ECS/Components/ColliderComponent.h>
#include <ECS/Components/SingletonPhysicsContactInfo.h>
#include <Util/PhysicsContactListener.h>


void zv::PhysicsContactListener::BeginContact(b2Contact* ptr_contact)
{
  ZV_ASSERT(m_ptr_contact_info != nullptr);

  auto* ptr_collider_a = reinterpret_cast<zv::ColliderComponent*>(ptr_contact->GetFixtureA()->GetBody()->GetUserData().pointer);
  auto* ptr_collider_b = reinterpret_cast<zv::ColliderComponent*>(ptr_contact->GetFixtureB()->GetBody()->GetUserData().pointer);
  m_ptr_contact_info->record_contact_event(ptr_collider_a->object_id(), PhysicsContact::eType::Begin, ptr_collider_b);
  m_ptr_contact_info->record_contact_event(ptr_collider_b->object_id(), PhysicsContact::eType::Begin, ptr_collider_a);
  // u32 ndx = m_contactEventList.size;
  // m_contactEventList.events[ndx].ptr_contact = ptr_contact;
  // m_contactEventList.events[ndx].type = ContactEvent::eType::Begin;
  // m_contactEventList.size++;
}

void zv::PhysicsContactListener::EndContact(b2Contact* ptr_contact)
{
  ZV_ASSERT(m_ptr_contact_info != nullptr);

  // u32 ndx = m_contactEventList.size;
  // m_contactEventList.events[ndx].ptr_contact = ptr_contact;
  // m_contactEventList.events[ndx].type = ContactEvent::eType::End;
  // m_contactEventList.size++;
}

// void zv::PhysicsContactListener::PreSolve(b2Contact* ptr_contact, const b2Manifold* ptr_old_manifold)
// {
//   m_contactEventList.events[ndx].ptr_contact = ptr_contact;
//   m_contactEventList.events[ndx].type = ContactEvent::eType::PreSolve;
//   m_contactEventSize++;
// }

// void zv::PhysicsContactListener::PostSolve(b2Contact* ptr_contact, const b2ContactImpulse* ptr_impulse)
// {
//   m_contactEventList.events[ndx].ptr_contact = ptr_contact;
//   m_contactEventList.events[ndx].type = ContactEvent::eType::PostSolve;
//   m_contactEventSize++;
// }
