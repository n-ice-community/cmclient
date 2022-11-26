// This file is generated by gen_commands.py, do not edit

#include "cm_gen_commands.cpp"
namespace citymania {
namespace cmd {

bool ModifyOrder::Post(bool automatic) {
    return ::Command<CMD_MODIFY_ORDER>(this->flags, this->veh, this->sel_ord, this->mof, this->data);
}

bool SkipToOrder::Post(bool automatic) {
    return ::Command<CMD_SKIP_TO_ORDER>(this->flags, this->veh_id, this->sel_ord);
}

bool DeleteOrder::Post(bool automatic) {
    return ::Command<CMD_DELETE_ORDER>(this->flags, this->veh_id, this->sel_ord);
}

bool InsertOrder::Post(bool automatic) {
    return ::Command<CMD_INSERT_ORDER>(this->flags, this->veh, this->sel_ord, this->new_order);
}

bool OrderRefit::Post(bool automatic) {
    return ::Command<CMD_ORDER_REFIT>(this->flags, this->veh, this->order_number, this->cargo);
}

bool CloneOrder::Post(bool automatic) {
    return ::Command<CMD_CLONE_ORDER>(this->flags, this->action, this->veh_dst, this->veh_src);
}

bool MoveOrder::Post(bool automatic) {
    return ::Command<CMD_MOVE_ORDER>(this->flags, this->veh, this->moving_order, this->target_order);
}

bool ClearOrderBackup::Post(bool automatic) {
    return ::Command<CMD_CLEAR_ORDER_BACKUP>(this->flags, this->tile, this->user_id);
}

bool CreateStoryPage::Post(bool automatic) {
    return ::Command<CMD_CREATE_STORY_PAGE>(this->flags, this->company, this->text);
}

bool CreateStoryPageElement::Post(bool automatic) {
    return ::Command<CMD_CREATE_STORY_PAGE_ELEMENT>(this->flags, this->tile, this->page_id, this->type, this->reference, this->text);
}

bool UpdateStoryPageElement::Post(bool automatic) {
    return ::Command<CMD_UPDATE_STORY_PAGE_ELEMENT>(this->flags, this->tile, this->page_element_id, this->reference, this->text);
}

bool SetStoryPageTitle::Post(bool automatic) {
    return ::Command<CMD_SET_STORY_PAGE_TITLE>(this->flags, this->page_id, this->text);
}

bool SetStoryPageDate::Post(bool automatic) {
    return ::Command<CMD_SET_STORY_PAGE_DATE>(this->flags, this->page_id, this->date);
}

bool ShowStoryPage::Post(bool automatic) {
    return ::Command<CMD_SHOW_STORY_PAGE>(this->flags, this->page_id);
}

bool RemoveStoryPage::Post(bool automatic) {
    return ::Command<CMD_REMOVE_STORY_PAGE>(this->flags, this->page_id);
}

bool RemoveStoryPageElement::Post(bool automatic) {
    return ::Command<CMD_REMOVE_STORY_PAGE_ELEMENT>(this->flags, this->page_element_id);
}

bool StoryPageButton::Post(bool automatic) {
    return ::Command<CMD_STORY_PAGE_BUTTON>(this->flags, this->tile, this->page_element_id, this->reference);
}

}  // namaespace cmd
}  // namaespace citymania
